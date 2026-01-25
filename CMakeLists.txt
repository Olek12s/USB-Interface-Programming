cmake_minimum_required(VERSION 3.28)
project(USB-Interface-Programming LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/src/main.cpp
        src/src/Renderer.cpp
        src/include/Renderer.h
        src/src/RoundedRectangleShape.cpp
        src/include/RoundedRectangleShape.h
        src/src/Ball.cpp
        src/include/Ball.h
        src/src/Paddle.cpp
        src/include/Paddle.h
        src/src/Block.cpp
        src/include/Block.h
        src/src/Updater.cpp
        src/include/Updater.h
        src/src/Game.cpp
        src/include/Game.h
        src/src/Input.cpp
        src/include/Input.h)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)