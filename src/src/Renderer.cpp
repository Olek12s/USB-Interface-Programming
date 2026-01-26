//
// Created by Oleki on 19.01.2026.
//

#include "../include/Renderer.h"

#include <iostream>

#include "SFML/Graphics/Color.hpp"
#include "../include/RoundedRectangleShape.h"
#include "../include/Game.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

sf::RenderWindow Renderer::window;
sf::View Renderer::view;

void Renderer::createWindow(unsigned int width, unsigned int height, const std::string& title)
{
    window.create(sf::VideoMode({width, height}), title);
    window.setFramerateLimit(60);

    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Failed to load font\n";
    }
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
    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {
            renderBlock(block);
        }
    }

    renderPaddleAllowedArea();
    renderBlocksBorder();
    renderPaddle(Game::getPaddle());
    Renderer::renderBall(Game::getBall());
    renderGUI();
}

void Renderer::renderGUI() {
    sf::Text highScoreText(font);
    sf::Text scoreText(font);

    highScoreText.setCharacterSize(40);
    scoreText.setCharacterSize(40);
    highScoreText.setOutlineThickness(2);
    scoreText.setOutlineThickness(2);

    sf::Color textColor = sf::Color{10, 25, 230};
    highScoreText.setFillColor(textColor);
    scoreText.setFillColor(textColor);

    highScoreText.setString("Highscore: " + std::to_string(Game::getHighScore()));
    scoreText.setString("Score: " + std::to_string(Game::getScore()));

    highScoreText.setPosition({10.f, 5.f});
    scoreText.setPosition({10.f, 45.f});

    window.draw(highScoreText);
    window.draw(scoreText);
}


void Renderer::renderPaddle(Paddle& paddle) {
    sf::RectangleShape rect;

    rect.setSize({paddle.getWidth(), paddle.getHeight()});
    rect.setPosition(paddle.getPosition());
    rect.setFillColor(sf::Color(200, 200, 200));

    window.draw(rect);
}

void Renderer::renderBall(Ball& ball) {
    sf::CircleShape c(ball.getRadius());

    c.setOrigin({ball.getRadius(), ball.getRadius()}); // middle of the ball
    c.setPosition(ball.getPosition());
    c.setFillColor(sf::Color::White);
    window.draw(c);
}


void Renderer::renderBlock(Block& block) {
    //sf::RoundedRectangleShape rect;
    sf::RectangleShape rect;
    rect.setSize({Block::getWidth(), Block::getHeight()});
    rect.setPosition(block.getPosition());
    if (block.getHealth() == 3) rect.setFillColor(sf::Color::Green);
    else if (block.getHealth() == 2) rect.setFillColor(sf::Color::Yellow);
    else rect.setFillColor(sf::Color::Red);
    window.draw(rect);
}

void Renderer::renderPaddleAllowedArea() {
    sf::RectangleShape rect;

    float height = Game::getPaddleYBorder();
    float y = view.getSize().y - height;

    rect.setPosition({0.f, y});
    rect.setSize({view.getSize().x, height});
    rect.setFillColor(sf::Color(0, 0, 128, 180));
    window.draw(rect);
}

void Renderer::renderBlocksBorder() {
    sf::RectangleShape line;

    float height = view.getSize().y - Game::getBlockYBorder();
    float thickness = 4.f;
    line.setPosition({0.f, height - thickness/2.f}); // centering line in Y axis
    line.setSize({view.getSize().x, thickness});
    line.setFillColor(sf::Color(128, 0, 0, 200));
    window.draw(line);
}


