//
// Created by Oleki on 24.01.2026.
//

#ifndef PADDLE_H
#define PADDLE_H
#include "SFML/System/Vector2.hpp"

class Paddle {
public:
    Paddle();

    void move(float xd, float yd);
    void render();
    float getWidth();
    float getHeight();
    sf::Vector2f getStartingPosition();
    float getMaxVelovityXY();
    void setPosition(sf::Vector2f p);
    sf::Vector2f getPosition();

private:
    sf::Vector2f pos;
    float width = 140.f;
    float height = 18.f;
    float maxVelovityXY = 25.f;

    bool moveX(float xd);
    bool moveY(float yd);
};



#endif //PADDLE_H
