//
// Created by Oleki on 24.01.2026.
//

#include "../include/Game.h"
#include "../include/Input.h"
#include "../include/Updater.h"
#include "../include/Renderer.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

std::vector<std::vector<Block>>& Game::getBlocks() {
    return blocks;
}

Game::Game() {
    pending = false;
    score = 0;
    highScore = 0;
    Block::setWidth(blockWidth);
    Block::setHeight(blockHeight);
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

float Game::getBlockDeclinationSpeed() {
    return blockDeclinationSpeed;
}

float Game::getViewWidth() {
    return viewWidth;
}
float Game::getViewHeight() {
    return viewHeight;
}

void Game::start() {
    generate();
}

void Game::restart() {
    generate();
    paddle.setPosition({paddle.getStartingPosition()});    // set paddle position on the middle
    ball.setPosition(Ball::getDefaultPos());
    ball.setDir(Ball::getDefaultDir());
    resetScore();
}


bool Game::isPending() {
    return pending;
}

void Game::setPending(bool pend) {pending = pend;}

int Game::getScore() {return score;}
int Game::getHighScore() {return highScore;}

void Game::addScore(int s) {
    score += s;
    if (score > highScore) highScore = score;
}
void Game::resetScore() {score = 0;}
void Game::setHighScore(int s) {highScore = s;}

float Game::getBlockYBorder() {
    return blocksBottomYBorder;
}

float Game::getPaddleYBorder() {
    return paddleBottomYBorder;
}

Paddle& Game::getPaddle() {return paddle;}
Ball& Game::getBall() {return ball;}

void Game::generate() {
    blocks.clear();

    float blockWidthAdjusted = (viewWidth - (blocksInRow - 1) * PADDING) / blocksInRow;
    Block::setWidth(blockWidthAdjusted);
    Block::setHeight(blockHeight);

    float startX = 0.f;

    for (int row = 0; row < rowsAtStart; row++)
    {
        std::vector<Block> line;

        for (int col = 0; col < blocksInRow; col++)
        {
            float x = startX + col * (blockWidthAdjusted + PADDING);
            float y = row * (blockHeight + PADDING);
            line.emplace_back(sf::Vector2f(x, y));
        }
        blocks.push_back(line);
    }
}

void Game::generateNewRow() {
    float blockWidthAdjusted = (viewWidth - (blocksInRow - 1) * PADDING) / blocksInRow;
    Block::setWidth(blockWidthAdjusted);
    Block::setHeight(blockHeight);

    float rowHeight = blockHeight + PADDING;


    // Y above previous row
    float newRowY = 0.f; // no rows yet
    if (!blocks.empty()) {
        newRowY = blocks[0][0].getPosition().y - rowHeight;
    }

    // generate new row
    std::vector<Block> newRow;
    for (int col = 0; col < blocksInRow; col++) {
        float x = col * (blockWidthAdjusted + PADDING);
        newRow.emplace_back(sf::Vector2f(x, newRowY));
    }

    // insert new row into the beggining
    blocks.insert(blocks.begin(), std::move(newRow));
}

float Game::getPadding() {
    return PADDING;
}


void Game::mainLoop()
{
    constexpr int TARGET_TPS = 60;
    const double nsPerTick = 1'000'000'000.0 / TARGET_TPS;

    Renderer::createWindow(viewWidth, viewHeight, "Breakout");

    // --- LETTERBOX VIEW ---
    sf::View mainView;
    mainView.setSize({viewWidth, viewHeight});
    mainView.setCenter({viewWidth/2.f, viewHeight/2.f});
    mainView = getLetterboxView(mainView, viewWidth, viewHeight);
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
    Input::init();
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
            //if (pending)
            {
                Input::update();
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

            //std::cout << "TPS: " << currentTPS<< " | FPS: " << currentFPS << std::endl;
        }
    }
}
