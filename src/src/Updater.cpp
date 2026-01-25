//
// Created by Oleki on 24.01.2026.
//

#include "../include/Updater.h"
#include "../include/Renderer.h"
#include <iostream>
#include <algorithm>
#include "../include/Game.h"

void Updater::globalTick() {
    // if game is stopped / not started - no ticks are performed
    if (!Game::isPending()) return;

    // Tick all existing blocks

    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {
            block.tick();
        }
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

    // Paddle movement
    //TODO: temporary movement system

    sf::RenderWindow& win = Renderer::getWindow();
    //sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    sf::Vector2i pixelPos = sf::Mouse::getPosition(win);
    sf::Vector2f viewPos = win.mapPixelToCoords(pixelPos);

    float mouseX = (float)viewPos.x;
    float mouseY = (float)viewPos.y;

    Paddle& paddle = Game::getPaddle();

    float paddleCenterX = paddle.getPosition().x + paddle.getWidth() / 2.f;
    float paddleCenterY = paddle.getPosition().y + paddle.getHeight() / 2.f;

    float diffX = mouseX - paddleCenterX;
    float diffY = mouseY - paddleCenterY;

    paddle.move(diffX, diffY);


    // ================= BALL =================

    Ball& ball = Game::getBall();
    ball.move();

    sf::Vector2f pos = ball.getPosition();
    float r = ball.getRadius();

    float w = Renderer::getWindow().getView().getSize().x;
    float h = Renderer::getWindow().getView().getSize().y;

    if (pos.x - r <= 0.f) {
        ball.bounceX();
        ball.setPosition({r, pos.y});
    }
    else if (pos.x + r >= w) {
        ball.bounceX();
        ball.setPosition({w - r, pos.y});
    }

    if (pos.y - r <= 0.f) {
        ball.bounceY();
        ball.setPosition({pos.x, r});
    }

    sf::FloatRect paddleRect(
        paddle.getPosition(),
        {paddle.getWidth(), paddle.getHeight()}
    );

    sf::FloatRect ballRect(
        {ball.getPosition().x - r, ball.getPosition().y - r},
        {r * 2.f, r * 2.f}
    );

    if (ballRect.findIntersection(paddleRect)) {

        ball.setPosition({
            ball.getPosition().x,
            paddle.getPosition().y - r
        });

        float paddleCenter = paddle.getPosition().x + paddle.getWidth() / 2.f;
        float diff = (ball.getPosition().x - paddleCenter) / (paddle.getWidth() / 2.f);

        sf::Vector2f newDir = { diff, -1.f };
        ball.setDir(newDir);
    }

    // BLOCKS
    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {

            sf::FloatRect blockRect(
                block.getPosition(),
                {Block::getWidth(), Block::getHeight()}
            );

            if (ballRect.findIntersection(blockRect)) {

                block.hit();

                float bx = ball.getPosition().x;
                float by = ball.getPosition().y;

                auto& p = blockRect.position;
                auto& s = blockRect.size;

                float left   = std::abs(bx - p.x);
                float right  = std::abs(bx - (p.x + s.x));
                float top    = std::abs(by - p.y);
                float bottom = std::abs(by - (p.y + s.y));

                if (std::min(left, right) < std::min(top, bottom)) {
                    ball.bounceX();

                    if (left < right)
                        ball.setPosition({p.x - r, by});
                    else
                        ball.setPosition({p.x + s.x + r, by});
                }
                else {
                    ball.bounceY();

                    if (top < bottom)
                        ball.setPosition({bx, p.y - r});
                    else
                        ball.setPosition({bx, p.y + s.y + r});
                }
                return;
            }
        }


        auto& blocks = Game::getBlocks();

        // Removing dead blocks
        for (auto& row : blocks) {
            for (auto it = row.begin(); it != row.end(); ) {
                if (!it->isAlive()) {
                    std::cout << "Removed block\n";
                    it = row.erase(it); // erase returns the next iterator
                } else {
                    ++it;
                }
            }
        }

        // Remove empty rows
        for (auto it = blocks.begin(); it != blocks.end(); ) {
            if (it->empty()) {
                std::cout << "Removed empty row\n";
                it = blocks.erase(it); // erase returns the next iterator
            } else {
                ++it;
            }
        }
    }
}
