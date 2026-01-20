#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class TicTacToeGrid : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape topline;
    sf::RectangleShape botline;
    sf::RectangleShape lefline;
    sf::RectangleShape rigline;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    TicTacToeGrid();
};

