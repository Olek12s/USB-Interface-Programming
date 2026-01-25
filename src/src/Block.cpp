//
// Created by Oleki on 24.01.2026.
//

#include "../include/Block.h"

#include <iostream>

#include "../include/Game.h"
#include "../include/Renderer.h"


Block::Block(sf::Vector2f p) : pos(p) {
    health = 3;
    alive = true;
}

bool Block::isAlive() {
    return alive;
}

void Block::render() {
    Renderer::renderBlock(*this);
}

void Block::hit() {
    health = std::max(0, health - 1);
    if (health == 0) {
        alive = false;  // marked to be removed on next tick
    }
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

