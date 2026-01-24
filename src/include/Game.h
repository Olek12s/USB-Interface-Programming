//
// Created by Oleki on 24.01.2026.
//

#ifndef GAME_H
#define GAME_H



class Game {
public:
    Game() : pending(false), score(0) {}

private:
    bool pending = false;
    int score;
};



#endif //GAME_H
