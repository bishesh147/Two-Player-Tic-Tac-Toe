#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"

class CrossShape : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape line1;
    sf::RectangleShape line2;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void setup(int pos);
};


class GameEndLines : public sf::Drawable, public sf::Transformable {
private:
    sf::RectangleShape line;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    void setup(int pos);
};

