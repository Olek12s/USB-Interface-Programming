//
// Created by Oleki on 24.01.2026.
//

#ifndef GAME_H
#define GAME_H



class Game {
public:
    Game() : pending(false), score(0) {}
    void restart();
    void start();
    void generate();        // generate whole new starting setup of Blocks
    void generateNewRow();  // generate single row of blocks
    void mainLoop();

private:
    bool pending = false;   // game ticks only when pending true
    int score;
    int highScore;
    static int seed;
};



#endif //GAME_H
