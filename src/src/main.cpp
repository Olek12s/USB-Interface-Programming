#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "../include/RoundedRectangleShape.h"
#include "../include/Game.h"

using namespace std;


int main()
{
    Game game;
    game.start();
    game.mainLoop();
    return 0;

    constexpr unsigned int initResX = 1366;
    constexpr unsigned int initResY = 768;
    constexpr float vwX = 1366;
    constexpr float vwY = 768;

   //  auto window = sf::RenderWindow(sf::VideoMode({initResX, initResY}), "CMake SFML Project");
   //  window.setFramerateLimit(60);
   //
   //  sf::View view;
   //  view.setSize(sf::Vector2f(vwX, vwY));
   //  view.setCenter(sf::Vector2f(vwX/2, vwY/2));
   // // view = getLetterboxView(view, vwX, vwY);
   //
   //  while (window.isOpen())
   //  {
   //      while (const std::optional event = window.pollEvent())
   //      {
   //          if (event->is<sf::Event::Closed>())
   //          {
   //              std::cout << "[Event] closed\n";
   //
   //              window.close();
   //          }
   //          if (event->is<sf::Event::Resized>()) {
   //              std::cout << "[Event] resized\n";
   //              const unsigned int newW = window.getSize().x;
   //              const unsigned int newH = window.getSize().y;
   //
   //              std::cout << "w " << newW << "h " << newH << "\n";
   //              //view = getLetterboxView(view, static_cast<float>(newW), static_cast<float>(newH));
   //              std::cout << "vw " << view.getSize().x << ", vh " << view.getSize().y << "\n";
   //              window.setView(view);
   //          }
   //      }
   //      window.clear(sf::Color(0,0,0)); // fill letterbox background (outside view)
   //      sf::RectangleShape bgRect({view.getSize().x, view.getSize().y});    // fill the view area (inside letterbox)
   //      bgRect.setFillColor(sf::Color(22,22,22));
   //      window.draw(bgRect);
   //
   //      sf::CircleShape shape1(300.f);
   //      shape1.setFillColor(sf::Color(100, 250, 50));
   //      window.draw(shape1);
   //
   //      sf::CircleShape shape2(50.f);
   //      shape2.setFillColor(sf::Color(100, 250, 50));
   //      window.draw(shape2);
   //
   //      sf::CircleShape shape3(50.f);
   //      shape3.setPosition({30, 20});
   //      shape3.setFillColor(sf::Color(100, 50, 50));
   //      window.draw(shape3);
   //
   //      sf::FloatRect shape4({25, 100}, {75, 150});
   //      //window.draw(shape4);  - zle, trzeba miec RectangleShape
   //      sf::RectangleShape drawableRect;
   //      drawableRect.setSize({shape4.size.x, shape4.size.y});
   //      drawableRect.setPosition({shape4.position.x, shape4.position.y});
   //      drawableRect.setFillColor(sf::Color::Magenta);
   //      window.draw(drawableRect);
   //
   //      //TODO: klasy pokroju FloatRect, IntRect mają metody z wykrywaniem kolizji dla innych prostokątów.
   //      //TODO: Klasy typu CircleShape, RectangleShape służą jedynie do renderu, nie mają wykrywania kolizji
   //      //TODO: Trzeba więc samemu dopisać kolizje albo użyć czego innego :)
   //
   //      float rrW = 150;
   //      float rrH = 150;
   //      sf::RoundedRectangleShape roundedRect({rrW,rrH}, 15,10);
   //      roundedRect.setPosition({vwX/2 - rrW/2, vwY/2 - rrH/2});
   //      roundedRect.setFillColor(sf::Color::Red);
   //      window.draw(roundedRect);
   //
   //      //TODO: moze sie przydac do kolizji - zwraca rect
   //      sf::FloatRect bounds = roundedRect.getGlobalBounds();
   //      std::cout << "size: " << "x: " << bounds.size.x << " y: " << bounds.size.y << "\n";
   //      std::cout << "position: " << "x: " << bounds.position.x << " y: " << bounds.position.y << "\n";
   //
   //      window.display();
   //  }
}
