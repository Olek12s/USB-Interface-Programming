//
// Created by Oleki on 24.01.2026.
//

#include "../include/Block.h"

#include "../include/Renderer.h"

float Block::w = 133.f;
float Block::h = 35.f;

Block::Block(sf::Vector2f p) : pos(p) {}

void Block::render() {
    Renderer::renderBlock(*this);
}

float Block::getWidth() {
    return w;
}

float Block::getHeight() {
    return h;
}

int Block::getHealth() {
    return health;
}

sf::Vector2f Block::getPosition() {
    return pos;
}

