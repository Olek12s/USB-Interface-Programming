//
// Created by Oleki on 24.01.2026.
//

#ifndef BALL_H
#define BALL_H
#include "SFML/System/Vector2.hpp"


class Ball {
public:
    Ball(sf::Vector2f pos, sf::Vector2f dir);
    void move();
    void bounceX();
    static sf::Vector2f getDefaultDir();
    static sf::Vector2f getDefaultPos();
    void bounceY();
    void render();
    void tick();
    sf::Vector2f getPosition();
    float getRadius();
    void setPosition(sf::Vector2f p);
    void setDir(sf::Vector2f dir);

private:
    sf::Vector2f pos;       // position
    sf::Vector2f dir;       // dir vec
    float speed = 4.f;            // speed
    float maxSpeed = 8.f;
    float minSpeed = 2.f;
    static inline float radius = 10.f;           // r
};



#endif //BALL_H
