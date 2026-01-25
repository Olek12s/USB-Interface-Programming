//
// Created by Oleki on 24.01.2026.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Block.h"
#include "SFML/Graphics/View.hpp"


class Game {
public:
    Game();
    static std::vector<std::vector<Block>>& getBlocks();
    void restart();
    void start();
    void generate();        // generate whole new starting setup of Blocks
    void generateNewRow();  // generate single row of blocks
    void mainLoop();
    sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight);
    static float getBlockDeclinationSpeed();

private:
    bool pending = false;   // game ticks only when pending true
    int score;
    int highScore;
    static inline int seed;

    // block settings
    static inline std::vector<std::vector<Block>> blocks;
    static constexpr int blocksInRow = 10;
    static constexpr int blockInColAtStart = 7;
    static constexpr float blockWidth = 30.f;
    static constexpr float blockHeight = 15.f;
    static inline float blockDeclinationSpeed = 2.f;
};



#endif //GAME_H
