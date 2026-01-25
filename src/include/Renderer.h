//
// Created by Oleki on 19.01.2026.
//

#ifndef USB_INTERFACE_PROGRAMMING_RENDERER_H
#define USB_INTERFACE_PROGRAMMING_RENDERER_H
#include "Block.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Window.hpp"


class Renderer {
public:
    static void globalRender();
    static void renderBall();
    static void renderBlock(Block& block);
    static void renderPaddle();
    static void renderGUI();
    static void renderPaddleAllowedArea();
    static void createWindow(unsigned int width, unsigned int height, const std::string& title);
    static sf::RenderWindow& getWindow();
    static void setView(sf::View& view);

private:
    static sf::RenderWindow window;
    static sf::View view;
};


#endif //USB_INTERFACE_PROGRAMMING_RENDERER_H