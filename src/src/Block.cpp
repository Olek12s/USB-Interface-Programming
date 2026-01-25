//
// Created by Oleki on 24.01.2026.
//

#include "../include/Block.h"

#include <iostream>

#include "../include/Game.h"
#include "../include/Renderer.h"


Block::Block(sf::Vector2f p) : pos(p) {}

void Block::render() {
    Renderer::renderBlock(*this);
}

void Block::tick() {
    pos.y += Game::getBlockDeclinationSpeed();
}

float Block::getWidth() {
    return w;
}

float Block::getHeight() {
    return h;
}

void Block::setWidth(float width) {
    w = width;
}

void Block::setHeight(float height) {
    h = height;
}


int Block::getHealth() {
    return health;
}

sf::Vector2f Block::getPosition() {
    return pos;
}

