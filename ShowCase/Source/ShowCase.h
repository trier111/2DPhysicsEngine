#pragma once

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Core/Engine.h"
#include "Shape.h"

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

    void DrawAllShapes();

    void SpawnCircle(float Radius, const FVector2D& Position, bool IsDynamic);

    void SpawnAABB(const FVector2D& Size, const FVector2D& Position, bool IsDynamic);

    void SpawnLevel();

private:

    std::vector<std::unique_ptr<Shape>> Shapes;

};
