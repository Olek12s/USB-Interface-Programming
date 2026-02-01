//
// Created by Oleki on 25.01.2026.
//

#include "../include/Input.h"

void Input::init() {
    HidD_GetHidGuid(&hidGuid);  // get GUID of the HID device class
    enumerateDevices();         // enumerate HID devices and keep only gamepads/joysticks

    // first reads are async
    for(auto& dev : devices) {
        ReadFile(dev.handle, dev.buffer.data(), dev.reportSize, NULL, &dev.ov);
    }

    std::cout << "Input system initialized\n";
}

// Input::Input() {
//     HidD_GetHidGuid(&hidGuid);  // get GUID of the HID device class
//     enumerateDevices();         // enumerate HID devices and keep only gamepads/joysticks
//
//     // first reads are async
//     for(auto& dev : devices) {
//         ReadFile(dev.handle, dev.buffer.data(), dev.reportSize, NULL, &dev.ov);
//     }
// }

// Input::~Input() {
//     for(const auto& dev : devices) {
//         CloseHandle(dev.ov.hEvent);
//         CloseHandle(dev.handle);
//         HidD_FreePreparsedData(dev.ppd);
//     }
//     SetupDiDestroyDeviceInfoList(devInfo);
// }


// normalizes stick X or Y value into value in range of [-1, 1]
double Input::normalizeStick(LONG value)
{
    double result = (value - STICK_MIDDLE_VALUE) / STICK_MIDDLE_VALUE; // [-1, 1]
    return std::round(result * 10000.0) / 10000.0;
}

// normalizes trigger X or Y value into value in range of [-1, 1]
double Input::normalizeTrigger(LONG value)
{
    double result = (value - TRIGGER_MIDDLE_VALUE - TRIGGERS_OFFSET) / (TRIGGER_MIDDLE_VALUE - TRIGGERS_OFFSET); // [-1, 1]
    return std::round(result * 10000.0) / 10000.0;
}



// === Enumerate all HID devices, filter only joysticks/gamepads === //
void Input::enumerateDevices() {
devInfo = SetupDiGetClassDevs(&hidGuid, NULL, NULL,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if(devInfo == INVALID_HANDLE_VALUE) return;

    ifData.cbSize = sizeof(ifData);
    DWORD index = 0;

    cout << "HID Enumeration...\n";

    while(SetupDiEnumDeviceInterfaces(devInfo, NULL, &hidGuid, index++, &ifData))
    {
        // === Get path to the device === //
        DWORD size = 0;
        SetupDiGetDeviceInterfaceDetail(devInfo, &ifData, NULL, 0, &size, NULL);

        BYTE* raw = new BYTE[size];
        auto detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)raw;
        detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if(!SetupDiGetDeviceInterfaceDetail(devInfo, &ifData, detail, size, NULL, NULL)) {
            delete[] raw;
            continue;
        }
        // === Get path to the device === //

        HANDLE hDev = CreateFile(detail->DevicePath, GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

        delete[] raw;
        if(hDev == INVALID_HANDLE_VALUE) continue;

        // === Get HID Descriptor === //
        PHIDP_PREPARSED_DATA ppd;
        HIDP_CAPS caps;

        if(!HidD_GetPreparsedData(hDev, &ppd)) { CloseHandle(hDev); continue; }
        if(HidP_GetCaps(ppd, &caps) != HIDP_STATUS_SUCCESS) { HidD_FreePreparsedData(ppd); CloseHandle(hDev); continue; }
        // === Get HID Descriptor === //

        // === Filter out only GamePad / Joysticks === //
        bool isGameController =
            (caps.UsagePage == 0x01) &&
            (caps.Usage == HID_USAGE_GENERIC_JOYSTICK ||
             caps.Usage == HID_USAGE_GENERIC_GAMEPAD);

        if(!isGameController) {
            HidD_FreePreparsedData(ppd);
            CloseHandle(hDev);
            continue;
        }
        // === Filter out only GamePad / Joysticks === //

        // === Initialize HidGamePadDevice Structure === //
        HidGamePadDevice dev;
        initDevice(dev, hDev);
        devices.push_back(dev);
        cout << "OK: HID (buttons + trigger/stick)\n";
    }
}

// === Initialize HidGamePadDevice structure with buffer, overlapped and valueCaps === //
void Input::initDevice(HidGamePadDevice& dev, HANDLE hDev) {
    PHIDP_PREPARSED_DATA ppd;
    HIDP_CAPS caps;
    dev.handle = hDev;

    HidD_GetPreparsedData(hDev, &ppd);
    HidP_GetCaps(ppd, &caps);

    dev.ppd = ppd;
    dev.reportSize = caps.InputReportByteLength;
    dev.buffer.resize(dev.reportSize);

    ZeroMemory(&dev.ov, sizeof(OVERLAPPED));
    dev.ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    // getting ValueCaps (description of triggers / sticks)
    USHORT valCapsLen = 0;
    HidP_GetValueCaps(HidP_Input, nullptr, &valCapsLen, ppd);
    if(valCapsLen > 0) {
        dev.valueCaps.resize(valCapsLen);
        HidP_GetValueCaps(HidP_Input, dev.valueCaps.data(), &valCapsLen, ppd);
        dev.lastValues.resize(valCapsLen, 0);
    }
}

// === Read all input from device (buttons, triggers, sticks) === //
void Input::readInput(HidGamePadDevice& dev) {
    DWORD bytesRead;
    GetOverlappedResult(dev.handle, &dev.ov, &bytesRead, FALSE);

    // === buttons handling === //
    ULONG count = 16;
    USAGE btns[16];

    if(HidP_GetUsages(HidP_Input, HID_USAGE_PAGE_BUTTON, 0,
        btns, &count, dev.ppd, (PCHAR)dev.buffer.data(), dev.reportSize) == HIDP_STATUS_SUCCESS)
    {
        buttons.assign(btns, btns + count);
    }

    // === Reading all ValueCaps (triggers / sticks) === //
    for(auto& vc : dev.valueCaps) {
        if(vc.UsagePage != HID_USAGE_PAGE_GENERIC)
            continue;

        USAGE usage = vc.IsRange ? vc.Range.UsageMin : vc.NotRange.Usage;

        LONG value = 0;
        if(HidP_GetUsageValue(HidP_Input, vc.UsagePage, 0, usage,
            (PULONG)&value, dev.ppd, (PCHAR)dev.buffer.data(), dev.reportSize) != HIDP_STATUS_SUCCESS)
            continue;

        switch(usage) {
            case HID_USAGE_GENERIC_X:
                dev.leftX = value;
                dev.normalLeftX = normalizeStick(value);
                break;
            case HID_USAGE_GENERIC_Y:
                dev.leftY = -value;
                dev.normalLeftY = -normalizeStick(value);
                break;
            case HID_USAGE_GENERIC_RX:
                dev.rightX = value;
                dev.normalRightX = normalizeStick(value);
                break;
            case HID_USAGE_GENERIC_RY:
                dev.rightY = -value;
                dev.normalRightY = -normalizeStick(value);
                break;
            case HID_USAGE_GENERIC_Z:
            case HID_USAGE_GENERIC_RZ:
                dev.triggers = value;
                dev.normalTriggers = normalizeTrigger(value);
                break;
        }
    }

    ResetEvent(dev.ov.hEvent);
    ReadFile(dev.handle, dev.buffer.data(), dev.reportSize, NULL, &dev.ov);
}

void Input::update() {
    for(auto& dev : devices) {
        readInput(dev);
    }
    //Sleep(sleepTime);
}

std::pair<float, float> Input::getLeftStickToPairNormal() {
    if (devices.empty()) return {0.0f, 0.0f};

    return {devices[0].normalLeftX, devices[0].normalLeftY
};
}

std::pair<float, float> Input::getRightStickToPairNormal() {
    if (devices.empty()) return {0.0f, 0.0f};

    return {devices[0].normalRightX, devices[0].normalRightY};
}

float Input::getTriggerNormal() {
    if (devices.empty()) return 0.0f;

    return devices[0].normalTriggers;
}


bool Input::isButtonHeld(USAGE button) {
    return std::find(buttons.begin(), buttons.end(), button) != buttons.end();
}

bool Input::isButtonHeld(Button button) {
    return isButtonHeld(static_cast<USAGE>(button));
}