//
// Created by Oleki on 24.01.2026.
//

#ifndef BALL_H
#define BALL_H
#include "SFML/System/Vector2.hpp"


class Ball {
public:
    Ball(sf::Vector2f pos, sf::Vector2f dir, float radius);
    void move();
    void bounceX();
    void bounceY();
    void render();

private:
    sf::Vector2f pos;       // position
    sf::Vector2f dir;       // dir vec
    float speed;            // speed
    float maxSpeed;
    float minSpeed;
    float radius;           // r
};



#endif //BALL_H
