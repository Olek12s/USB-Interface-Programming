//
// Created by Oleki on 24.01.2026.
//

#include "../include/Game.h"
#include "../include/Updater.h"
#include "../include/Renderer.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

std::vector<std::vector<Block>> Game::blocks;

std::vector<std::vector<Block> > Game::getBlocks() {
    return blocks;
}

/**
 *  Compares aspect ratio of the current window to the aspect ratio of the view
 *  and sets the viewport sizes to achieve letterboxing effect.
 *  This method should only be called on initialization and Window Resize event
 * @param view The view whose viewport will be adjusted to preserve aspect ratio.
 * @param windowWidth initial window width
 * @param windowHeight initial window height
 * @return view with adjusted size and position
 */
sf::View Game::getLetterboxView(sf::View view, float windowWidth, float windowHeight) {
    float windowRatio = (float) windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    // set target viewport
    //view.setViewport(sf::Rect<float>({posX, posY}, {sizeX, sizeY}));
    view.setViewport({{posX, posY}, {sizeX, sizeY}});
    return view;
}


void Game::start() {
    generate();
}

void Game::generate() {
    blocks.clear();

    constexpr int ROWS = 5;
    constexpr float START_Y = 60.f;
    constexpr float PADDING = 5.f;

    const float totalWidth = blocksInRow * Block::getWidth() +
                             (blocksInRow - 1) * PADDING;

    const float startX = (1366.f - totalWidth) / 2.f;

    for (int row = 0; row < ROWS; row++)
    {
        std::vector<Block> line;

        for (int col = 0; col < blocksInRow; col++)
        {
            float x = startX + col * (Block::getWidth() + PADDING);
            float y = START_Y + row * (Block::getHeight() + PADDING);


            line.emplace_back(sf::Vector2f(x, y));
        }

        blocks.push_back(line);
    }

    pending = true;
}


void Game::mainLoop()
{
    constexpr int TARGET_TPS = 60;
    const double nsPerTick = 1'000'000'000.0 / TARGET_TPS;

   // sf::RenderWindow window(sf::VideoMode({1366, 768}), "Breakout");
   // Renderer::setWindow(window);
   // window.setVerticalSyncEnabled(false);
    Renderer::createWindow(1366, 768, "Breakout");

    // --- LETTERBOX VIEW ---
    sf::View mainView;
    mainView.setSize({1366.f, 768.f});  //TODO: tidy
    mainView.setCenter({1366.f/2, 768.f/2});
    mainView = getLetterboxView(mainView, 1366.f, 768.f);
    Renderer::setView(mainView);

    using clock = std::chrono::high_resolution_clock;

    auto lastTime = clock::now();
    auto lastSecond = clock::now();

    double accumulator = 0.0;

    int ticksThisSecond = 0;
    int framesThisSecond = 0;
    int currentTPS = 0;
    int currentFPS = 0;

    sf::RenderWindow& window = Renderer::getWindow();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
            if (event->is<sf::Event::Resized>()) {
                std::cout << "[Event] resized\n";
                const unsigned int newW = window.getSize().x;
                const unsigned int newH = window.getSize().y;

                std::cout << "w " << newW << "h " << newH << "\n";
                mainView = getLetterboxView(mainView, static_cast<float>(newW), static_cast<float>(newH));
                std::cout << "vw " << mainView.getSize().x << ", vh " << mainView.getSize().y << "\n";
                window.setView(mainView);
            }
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
