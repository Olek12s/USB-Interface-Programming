//
// Created by Oleki on 24.01.2026.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Block.h"


namespace sf {
    class View;
}

class Game {
public:
    Game() : pending(false), score(0) {}
    static std::vector<std::vector<Block>> getBlocks();
    void restart();
    void start();
    void generate();        // generate whole new starting setup of Blocks
    void generateNewRow();  // generate single row of blocks
    void mainLoop();
    sf::View getLetterboxView(sf::View view, float windowWidth, float windowHeight);

private:
    bool pending = false;   // game ticks only when pending true
    int score;
    int highScore;
    static int seed;
    static std::vector<std::vector<Block>> blocks;
    const int blocksInRow = 10;
};



#endif //GAME_H
