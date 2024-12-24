#pragma once

#include <SFML/Graphics.hpp>

namespace sf 
{
    class RenderWindow;
}

class Shape
{
public:
    virtual ~Shape() {}

    virtual void Draw(sf::RenderWindow& window) = 0;
};

