#pragma once

#include <SFML/Graphics.hpp>
#include "Core/Engine.h"
#include "Defines.h"

class ShowCase
{

public:

    ShowCase();

    void Run();

private:

    sf::RenderWindow Window;
    sf::Clock Clock;
    Engine PhysicsEngine;
    sf::Font Font;
    sf::Text DebugText;

private:

    void ProcessEvents();

    void Update();

    void Render();
};
