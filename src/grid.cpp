#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "grid.hpp"

void TicTacToeGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(topline, states);
    target.draw(botline, states);
    target.draw(lefline, states);
    target.draw(rigline, states);
}

TicTacToeGrid::TicTacToeGrid() {
    sf::Vector2f hSize(Config::GridSize, Config::LineThickness);
    sf::Vector2f vSize(Config::LineThickness, Config::GridSize);

    topline.setSize(hSize);
    topline.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY + Config::CellSize));

    botline.setSize(hSize);
    botline.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY + Config::CellSize*2 + Config::LineThickness));

    lefline.setSize(vSize);
    lefline.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize, Config::GridOriginY));

    rigline.setSize(vSize);
    rigline.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize * 2 + Config::LineThickness, Config::GridOriginY));
}

