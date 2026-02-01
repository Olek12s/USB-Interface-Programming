//
// Created by Oleki on 25.01.2026.
//

#ifndef INPUT_H
#define INPUT_H


#define NOMINMAX
#include <windows.h>
#include <setupapi.h>
#include <hidsdi.h>
#include <hidpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <utility>
#include <algorithm>
#include <cmath>

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "hid.lib")

using namespace std;

#define TRIGGER_MIDDLE_VALUE 32768.0
#define STICK_MIDDLE_VALUE 32768.0
#define TRIGGERS_OFFSET 128

struct HidGamePadDevice
{
    HANDLE handle;      // handler to the device
    OVERLAPPED ov;      // async read
    vector<BYTE> buffer;// buffer of HID input report
    DWORD reportSize;   // report Size

    PHIDP_PREPARSED_DATA ppd;   // descriptor
    vector<USAGE> lastButtons;  // buttons state from previous read

    vector<LONG> lastValues;            // all ValueCaps values (ushort)
    vector<HIDP_VALUE_CAPS> valueCaps;  // description of sticks/triggers of gamepad (min/max, usage)

    double leftX = 0, leftY = 0;
    double rightX = 0, rightY = 0;

    double normalLeftX = 0, normalLeftY = 0;
    double normalRightX = 0, normalRightY = 0;

    double triggers = 0;
    double normalTriggers = 0;
};


class Input {
private:
    static inline  GUID hidGuid;       // unique GUID of HID devices. Used in devices enumeration
    static inline  HDEVINFO devInfo;   // set of all HID devices in the system
    static inline  SP_DEVICE_INTERFACE_DATA ifData;
    static inline  vector<HidGamePadDevice> devices;
    static inline  vector<USAGE> buttons;  // buttons state from previous read, all currently pressed buttons
    static inline int sleepTime = 5; // ? milliseconds between reads


    static double normalizeStick(LONG value);
    static double normalizeTrigger(LONG value);
    static void initDevice(HidGamePadDevice& dev, HANDLE hDev);
    static void readInput(HidGamePadDevice& dev);

protected:

public:
    enum class Button : USAGE {
        A = 1,
        B = 2,
        X = 3,
        Y = 4,

        LeftBumper  = 5,
        RightBumper = 6,

        LeftMiddle  = 7,
        RightMiddle = 8,

        LeftStick   = 9,
        RightStick  = 10
    };


    Input();
    ~Input();

    static void enumerateDevices();
    static void update();

    static const vector<USAGE>& getButtons() { return buttons; }
    static const vector<HidGamePadDevice>& getDevices() { return devices; }


    static std::pair<float, float> getLeftStickToPairNormal();
    static std::pair<float, float> getRightStickToPairNormal();
    static float getTriggerNormal();

    static bool isButtonHeld(USAGE button);
    static bool isButtonHeld(Button button);
};

#endif //INPUT_H
