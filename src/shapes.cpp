#include <iostream>
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "shapes.hpp"

void CrossShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(line1, states);
    target.draw(line2, states);
}

void CrossShape::setup(int pos) {
    int row = pos / 3;
    int col = pos % 3;

    float centerX = Config::GridOriginX + (col * Config::CellSize) + (col * Config::LineThickness) + (Config::CellSize / 2.f);
    float centerY = Config::GridOriginY + (row * Config::CellSize) + (row * Config::LineThickness) + (Config::CellSize / 2.f);

    line1.setSize({Config::CrossSize, Config::CrossThickness});
    line1.setOrigin({Config::CrossSize / 2, Config::CrossThickness / 2});
    line1.setPosition({centerX, centerY});
    line1.setRotation(sf::degrees(45));
    line1.setFillColor(sf::Color::Green);

    line2.setSize({Config::CrossSize, Config::CrossThickness});
    line2.setOrigin({Config::CrossSize / 2, Config::CrossThickness / 2});
    line2.setPosition({centerX, centerY});
    line2.setRotation(sf::degrees(135));
    line2.setFillColor(sf::Color::Green);
}


void GameEndLines::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(line, states);
}

void GameEndLines::setup(int pos) {
    if (pos == 8) return;
    line.setFillColor(sf::Color::White);
    float diagonalLength = std::sqrt(2*Config::CellSize*Config::CellSize);

    if (pos <= 2) {
        line.setSize({Config::GridSize, Config::LineThickness});
        line.setPosition({Config::GridOriginX, Config::GridOriginY + Config::CellSize / 2 + (pos*(Config::CellSize + Config::LineThickness))});
    }
    else if ((pos > 2) && (pos < 6)) {
        line.setSize({Config::LineThickness, Config::GridSize});
        line.setPosition({Config::GridOriginX + Config::CellSize / 2 + ((pos-3)*(Config::CellSize + Config::LineThickness)), Config::GridOriginY});
    }
    else if (pos == 6) {
        line.setRotation(sf::degrees(45));
        line.setSize(sf::Vector2f(diagonalLength*3, Config::LineThickness));
        line.setPosition(sf::Vector2f(Config::GridOriginX, Config::GridOriginY));
    }
    else if (pos == 7) {
        line.setRotation(sf::degrees(135));
        line.setSize(sf::Vector2f(diagonalLength*3, Config::LineThickness));
        line.setPosition(sf::Vector2f(Config::GridOriginX + Config::CellSize*3 + Config::LineThickness*2, Config::GridOriginY));
    }
}

