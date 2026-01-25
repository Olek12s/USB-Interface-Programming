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
    static void generate();        // generate whole new starting setup of Blocks
    static void generateNewRow();  // generate single row of blocks
    void mainLoop();
    sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight);
    static float getBlockDeclinationSpeed();
    static float getPadding();
    static bool isPending();

private:
    static inline float viewWidth = 1366.f;
    static inline float viewHeight = 768.f;

    static inline bool pending = false;   // game ticks only when pending true
    int score;
    int highScore;
    static inline int seed;

    // block settings
    static inline std::vector<std::vector<Block>> blocks;
    static constexpr int blocksInRow = 14;
    static constexpr int rowsAtStart = 7;
    static constexpr int blockInColAtStart = 7;
    static constexpr float blockWidth = 30.f;
    static constexpr float blockHeight = 15.f;
    static constexpr float PADDING = 5.f;
    static inline float blockDeclinationSpeed = 0.05f;
};

#endif //GAME_H
