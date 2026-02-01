//
// Created by Oleki on 24.01.2026.
//

#include "../include/Ball.h"
#include "../include/Renderer.h"
#include <cmath>

#include "../include/Game.h"

// converting a vector to a unit vector of length 1 while keeping its direction.
static sf::Vector2f normalize(sf::Vector2f v) {
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len == 0) return {0.f, 0.f};
    return {v.x/len, v.y/len};
}

void Ball::setPosition(sf::Vector2f p) { pos = p; }
void Ball::setDir(sf::Vector2f d) {dir = d;}

Ball::Ball(sf::Vector2f p, sf::Vector2f d)
: pos(p), dir(d) {}

void Ball::tick() {
    move();

    float w = Renderer::getWindow().getView().getSize().x;

    // bouncing from walls

    if (pos.x - radius <= 0.f) {
        bounceX();
    }
    else if (pos.x + radius >= w) {
        bounceX();
    }
    if (pos.y - radius <= 0.f) {
        bounceY();
    }

    // bouncing from paddle

    Paddle paddle = Game::getPaddle();

    sf::FloatRect paddleRect(
        paddle.getPosition(),
        {paddle.getWidth(), paddle.getHeight()}
    );

    sf::FloatRect ballRect(
        {pos.x - radius, pos.y - radius},
        {radius * 2.f, radius * 2.f}
    );

    if (ballRect.findIntersection(paddleRect))  // if ball intersected with paddle in current tick - bounce it by changing its direction
        {
        float paddleCenter = paddle.getPosition().x + paddle.getWidth() / 2.f;
        float diff = (pos.x - paddleCenter) / (paddle.getWidth() / 2.f);

        sf::Vector2f newDir = { diff, -1.f };
        setDir(newDir);
    }


    // bouncing & damaging blocks

    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {

            sf::FloatRect blockRect(
                block.getPosition(),
                {Block::getWidth(), Block::getHeight()}
            );

            if (ballRect.findIntersection(blockRect)) {

                block.hit();

                float bx = pos.x;
                float by = pos.y;

                auto& p = blockRect.position;
                auto& s = blockRect.size;

                float left   = std::abs(bx - p.x);
                float right  = std::abs(bx - (p.x + s.x));
                float top    = std::abs(by - p.y);
                float bottom = std::abs(by - (p.y + s.y));

                if (std::min(left, right) < std::min(top, bottom)) {
                    bounceX();
                }
                else {
                    bounceY();
                }
            }
        }
    }
}

void Ball::move() {
    pos += dir * speed;
}

void Ball::bounceX() {
    dir.x *= -1.f;
}

void Ball::bounceY() {
    dir.y *= -1.f;
}

sf::Vector2f Ball::getDefaultDir() {
    return {0.f, -1.f};
}

sf::Vector2f Ball::getDefaultPos() {
    return {Game::getViewWidth()/2 - radius, 600.f};
}

void Ball::render() {
    Renderer::renderBall(*this);
}

sf::Vector2f Ball::getPosition() { return pos; }
float Ball::getRadius() { return radius; }