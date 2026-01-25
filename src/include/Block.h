//
// Created by Oleki on 24.01.2026.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "SFML/System/Vector2.hpp"


class Block {
public:
    Block(sf::Vector2f pos);
    static float getWidth();
    static float getHeight();
    static void setWidth(float w);
    static void setHeight(float h);
    int getHealth();
    sf::Vector2f getPosition();
    bool isAlive();
    void hit();
    void render();
    void tick();

private:
    sf::Vector2f pos;
    static inline float w;
    static inline float h;
    int health;
    bool alive;
};



#endif //BLOCK_H
