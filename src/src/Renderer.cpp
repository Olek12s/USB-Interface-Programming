//
// Created by Oleki on 19.01.2026.
//

#include "../include/Renderer.h"

#include <iostream>

#include "SFML/Graphics/Color.hpp"
#include "../include/RoundedRectangleShape.h"
#include "../include/Game.h"
#include "SFML/Graphics/RectangleShape.hpp"

sf::RenderWindow Renderer::window;
sf::View Renderer::view;

void Renderer::createWindow(unsigned int width, unsigned int height, const std::string& title)
{
    window.create(sf::VideoMode({width, height}), title);
    window.setFramerateLimit(60);
}

sf::RenderWindow& Renderer::getWindow()
{
    return window;
}

void Renderer::setView(sf::View& v) {
    view = v;
    window.setView(v);
}


void Renderer::globalRender() {
    // Render letterbox
    window.clear(sf::Color(0,0,0)); // fill letterbox background (outside view)

    // Render background
    sf::RectangleShape bgRect({view.getSize().x, view.getSize().y});    // fill the view area (inside letterbox)
    bgRect.setFillColor({22, 22, 22});
    window.draw(bgRect);

    // Render all blocks
    for (auto& row : Game::getBlocks())
        for (auto& block : row)
            renderBlock(block);
}

void Renderer::renderBlock(Block& block) {
    //sf::RoundedRectangleShape rect;
    sf::RectangleShape rect;
    rect.setSize({Block::getWidth(), Block::getHeight()});
    rect.setPosition(block.getPosition());
    if (block.getHealth() == 3) rect.setFillColor(sf::Color::Red);
    else if (block.getHealth() == 2) rect.setFillColor(sf::Color::Yellow);
    else rect.setFillColor(sf::Color::Green);
    window.draw(rect);
}

