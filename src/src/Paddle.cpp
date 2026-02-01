//
// Created by Oleki on 24.01.2026.
//

#include "../include/Paddle.h"

#include <algorithm>

#include "../include/Renderer.h"
#include "../include/Game.h"

Paddle::Paddle() {
    pos = getStartingPosition(); // start
}

sf::Vector2f Paddle::getStartingPosition() {return {600.f, 700.f};}
float Paddle::getWidth() { return width; }
float Paddle::getHeight() { return height; }
void Paddle::setPosition(sf::Vector2f p) { pos = p; }
sf::Vector2f Paddle::getPosition() { return pos; }


void Paddle::move(float xd, float yd)
{
    xd = std::clamp(xd, -maxVelovityXY, maxVelovityXY);
    yd = std::clamp(yd, -maxVelovityXY, maxVelovityXY);

    if (xd != 0.f) moveX(xd);
    if (yd != 0.f) moveY(yd);
}

bool Paddle::moveX(float xd)
{
    float newX = pos.x + xd;

    float minX = 0.f;
    float maxX = Game::getViewWidth() - width;

    if (newX < minX) newX = minX;
    if (newX > maxX) newX = maxX;

    pos.x = newX;
    return true;
}

bool Paddle::moveY(float yd)
{
    float newY = pos.y + yd;

    float bottom = Game::getViewHeight() - height;
    float top = 768.f - Game::getPaddleYBorder();   // paddle's movement is only within blue area
    if (newY < top) newY = top;
    if (newY > bottom) newY = bottom;

    pos.y = newY;
    return true;
}




void Paddle::render() {
    Renderer::renderPaddle(*this);
}
