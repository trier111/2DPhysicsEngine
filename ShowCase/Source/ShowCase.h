#pragma once

#include <SFML/Graphics.hpp>
#include "Defines.h"
#include "Core/Engine.h"
#include "Shape.h"
#include "ColorUtils.h"

class ShowCase
{

public:

	ShowCase();

	void Run();

private:

	sf::RenderWindow Window;
	sf::Clock Clock;
	Engine& PhysicsEngine;
	sf::Font Font;
	sf::Text DebugText;

private:

	void ProcessEvents();

	void Update();

	void TryToSpawnShape(float DeltaTime);

	void Render();

	void DrawAllShapes();

	void ClearMarkedShapes();

	void SpawnCircle(float Radius, const FVector2D& Position, bool IsDynamic, sf::Color InColor = ColorUtils::GetRandomPresetColor());

	void SpawnAABB(const FVector2D& Size, const FVector2D& Position, bool IsDynamic, sf::Color InColor = ColorUtils::GetRandomPresetColor());

	void SpawnLevel();

private:

	bool IsLeftMouseButtonPressed;

	bool IsRightMouseButtonPressed;

	float TimeSinceLastSpawn;

	std::vector<std::unique_ptr<Shape>> Shapes;

};
