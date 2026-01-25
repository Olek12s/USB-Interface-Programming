//
// Created by Oleki on 24.01.2026.
//

#include "../include/Ball.h"
#include "../include/Renderer.h"
#include <cmath>

// converting a vector to a unit vector of length 1 while keeping its direction.
static sf::Vector2f normalize(sf::Vector2f v) {
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len == 0) return {0.f, 0.f};
    return {v.x/len, v.y/len};
}

void Ball::setPosition(sf::Vector2f p) { pos = p; }
void Ball::setDir(sf::Vector2f d) {dir = d;}

Ball::Ball(sf::Vector2f p, sf::Vector2f d, float r)
: pos(p), dir(normalize(d)), radius(r) {}

void Ball::move() {
    pos += dir * speed;
}

void Ball::bounceX() {
    dir.x *= -1.f;
}

void Ball::bounceY() {
    dir.y *= -1.f;
}

void Ball::render() {
    Renderer::renderBall(*this);
}

sf::Vector2f Ball::getPosition() { return pos; }
float Ball::getRadius() { return radius; }