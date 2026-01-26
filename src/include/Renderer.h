//
// Created by Oleki on 19.01.2026.
//

#ifndef USB_INTERFACE_PROGRAMMING_RENDERER_H
#define USB_INTERFACE_PROGRAMMING_RENDERER_H
#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"
#include <SFML/Graphics/Font.hpp>


class Renderer {
public:
    static void globalRender();
    static void renderBall(Ball& ball);
    static void renderBlock(Block& block);
    static void renderPaddle(Paddle& paddle);
    static void renderGUI();
    static void renderPaddleAllowedArea();
    static void renderBlocksBorder();
    static void createWindow(unsigned int width, unsigned int height, const std::string& title);
    static sf::RenderWindow& getWindow();
    static void setView(sf::View& view);

private:
    static sf::RenderWindow window;
    static sf::View view;
    static inline sf::Font font;
};


#endif //USB_INTERFACE_PROGRAMMING_RENDERER_H