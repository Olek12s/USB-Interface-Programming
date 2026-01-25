//
// Created by Oleki on 24.01.2026.
//

#ifndef GAME_H
#define GAME_H
#include <vector>

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "SFML/Graphics/View.hpp"


class Game {
public:
    Game();
    static std::vector<std::vector<Block>>& getBlocks();
    static Paddle& getPaddle();
    static Ball& getBall();
    void restart();
    void start();
    static void generate();        // generate whole new starting setup of Blocks
    static void generateNewRow();  // generate single row of blocks
    void mainLoop();
    sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight);
    static float getBlockDeclinationSpeed();
    static float getPadding();
    static bool isPending();
    static float getPaddleYBorder();
    static float getBlockYBorder();
    static float getViewWidth();
    static float getViewHeight();

private:
    static inline float viewWidth = 1366.f;
    static inline float viewHeight = 768.f;

    static inline bool pending = false;   // game ticks only when pending true
    int score;
    int highScore;
    static inline int seed;

    // block settings
    static inline std::vector<std::vector<Block>> blocks;
    static inline Paddle paddle;
    static inline Ball ball = Ball({683.f, 500.f}, {0.6f, -1.f}, 10.f);
    static constexpr int blocksInRow = 7;
    static constexpr int rowsAtStart = 7;
    static constexpr int blockInColAtStart = 7;
    static constexpr float blockWidth = 0.f;
    static constexpr float blockHeight = 30.f;
    static constexpr float PADDING = 5.f;
    static inline float blockDeclinationSpeed = 0.05f;

    static inline float paddleBottomYBorder = 150.f;  // maximum height where paddle can be present
    static inline float blocksBottomYBorder = 200.f;   // when any block reaches this border - the game is over
};

#endif //GAME_H
