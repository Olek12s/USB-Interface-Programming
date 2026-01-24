//
// Created by Oleki on 24.01.2026.
//

#include "../include/Game.h"
#include "../include/Updater.h"
#include "../include/Renderer.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

void Game::mainLoop()
{
    constexpr int TARGET_TPS = 60;
    const double nsPerTick = 1'000'000'000.0 / TARGET_TPS;

    sf::RenderWindow window(sf::VideoMode({1366, 768}), "Breakout");
    window.setVerticalSyncEnabled(false);

    using clock = std::chrono::high_resolution_clock;

    auto lastTime = clock::now();
    auto lastSecond = clock::now();

    double accumulator = 0.0;

    int ticksThisSecond = 0;
    int framesThisSecond = 0;
    int currentTPS = 0;
    int currentFPS = 0;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        auto now = clock::now();
        double deltaNs = std::chrono::duration<double, std::nano>(now - lastTime).count();
        lastTime = now;

        accumulator += deltaNs / nsPerTick;


        while (accumulator >= 1.0)
        {
            if (pending)
            {
                //input.listen();
                 Updater::globalTick();
            }

            ticksThisSecond++;
            accumulator -= 1.0;
        }
        window.clear();
        // draw
        Renderer::globalRender();
        window.display();
        framesThisSecond++;

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastSecond).count() >= 1000)
        {
            currentTPS = ticksThisSecond;
            currentFPS = framesThisSecond;

            ticksThisSecond = 0;
            framesThisSecond = 0;
            lastSecond = now;

            std::cout << "TPS: " << currentTPS<< " | FPS: " << currentFPS << std::endl;
        }
    }
}
