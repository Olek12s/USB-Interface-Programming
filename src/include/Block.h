//
// Created by Oleki on 24.01.2026.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "SFML/System/Vector2.hpp"


class Block {
public:
    void render();

private:
    sf::Vector2f pos;
    static int w, h;
    int health;
};



#endif //BLOCK_H
