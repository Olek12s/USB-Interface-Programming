//
// Created by Oleki on 24.01.2026.
//

#include "../include/Updater.h"
#include "../include/Renderer.h"
#include <iostream>
#include <algorithm>
#include "../include/Game.h"
#include "../include/Input.h"

void Updater::globalTick() {
    // if game is stopped / not started - no ticks are performed, only input for restarting game
    if (!Game::isPending()) {
        // === Mouse left click restart === //

        // if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        //     Game::setPending(true);
        // }

        // === Mouse left click restart === //

        if (Input::isButtonHeld(Input::Button::X)) {
            Game::setPending(true);
        }
        return;
    }

    // Generate new row of blocks whenever it would start reaching view

    float rowHeight = Block::getHeight() + Game::getPadding();
    std::vector<std::vector<Block>>& blocks = Game::getBlocks();
    if (!blocks.empty()) {
        float topRowY = blocks[0][0].getPosition().y + Block::getHeight(); // y of virutal -1 row
        if (topRowY >= rowHeight)
        {
            Game::generateNewRow();
            std::cout << "new row\n";
        }
    }

    // === Mouse Paddle movement === //

    // sf::RenderWindow& win = Renderer::getWindow();
    // //sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    // sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
    // sf::Vector2f viewPos = win.mapPixelToCoords(pixelPos);
    //
    // float mouseX = (float)viewPos.x;
    // float mouseY = (float)viewPos.y;
    //
    // Paddle& paddle = Game::getPaddle();
    //
    // float paddleCenterX = paddle.getPosition().x + paddle.getWidth() / 2.f;
    // float paddleCenterY = paddle.getPosition().y + paddle.getHeight() / 2.f;
    // float diffX = mouseX - paddleCenterX;
    // float diffY = mouseY - paddleCenterY;
    //
    // paddle.move(diffX, diffY);

    // === Mouse Paddle movement === //

    // === Game Pad movement === //

    Paddle& paddle = Game::getPaddle();

    // normalized stick position [-1, 1]
    std::pair<float, float> normalLeft = Input::getLeftStickToPairNormal();
    std::pair<float, float> normalRight = Input::getRightStickToPairNormal();

    int yInversion = -1;

    float lX = normalLeft.first;
    float lY = normalLeft.second * yInversion;
    float rX = normalRight.first;
    float rY = normalRight.second * yInversion;

    float moveX = rX * paddle.getMaxVelovityXY() + lX * (paddle.getMaxVelovityXY() / 5.f);
    float moveY = rY * paddle.getMaxVelovityXY() + lY * (paddle.getMaxVelovityXY() / 5.f);

    paddle.move(moveX, moveY);

    // === Game Pad movement === //

    Ball& ball = Game::getBall();
    ball.tick();

    bool blockReachedBorder = false;
    float borderY = Game::getViewHeight() - Game::getBlockYBorder();

    for (auto& row : blocks) {
        for (auto& block : row) {
            float blockBottom = block.getPosition().y + Block::getHeight();

            if (blockBottom >= borderY) {
                blockReachedBorder = true;
                break;
            }
        }
        if (blockReachedBorder) break;
    }

    // if ball was lost or any block reached block border - game over
    if (ball.getPosition().y - ball.getRadius() > Game::getViewHeight() || blockReachedBorder) {
        std::cout << "game over\n";
        Game::restart();
        Game::setPending(false);
    }

    // BLOCKS tick()
    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {
            block.tick();
        }
    }

    // Removing dead blocks
    for (auto& row : blocks) {
        for (auto it = row.begin(); it != row.end(); ) {
            if (!it->isAlive()) {
                std::cout << "Removed block\n";
                it = row.erase(it); // erase returns the next iterator
            } else {
                it++;
            }
        }
    }

    // Remove empty rows
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        if (it->empty()) {
            std::cout << "Removed empty row\n";
            it = blocks.erase(it); // erase returns the next iterator
        } else {
            it++;
        }
    }
}
