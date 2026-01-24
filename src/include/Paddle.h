//
// Created by Oleki on 24.01.2026.
//

#ifndef PADDLE_H
#define PADDLE_H



class Paddle {
public:
    void move(float xd, float yd);
    void render();

private:
    bool moveX(float xd);
    bool moveY(float yd);
};



#endif //PADDLE_H
