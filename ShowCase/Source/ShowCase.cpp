#include "ShowCase.h"

#include "Defines.h"
#include "Circle.h"
#include "Core/CircleComponent.h"
#include "AABB.h"
#include "Core/AABBComponent.h"
#include <string>
#include <sstream>
#include <cassert>

ShowCase::ShowCase(): 
	Window(sf::VideoMode(ShowcaseConfig::WINDOW_WIDTH, ShowcaseConfig::WINDOW_HEIGHT), "Showcase with Physics Engine"),
	PhysicsEngine(Engine::GetInstance()),
	IsLeftMouseButtonPressed(false),
	IsRightMouseButtonPressed(false),
	TimeSinceLastSpawn(0.f),
	CurrentShape(EShapeType::Circle)
{
	Window.setFramerateLimit(ShowcaseConfig::MAX_FPS);

	bool FontLoaded = Font.loadFromFile("../Fonts/PressStart2P-Regular.ttf");
	assert(FontLoaded && "Font failed to load!");

	DebugText.setFont(Font);
	DebugText.setCharacterSize(16);
	DebugText.setFillColor(sf::Color::Green);
	DebugText.setPosition(10.f, 10.f);
}

void ShowCase::Run() 
{
	SpawnLevel();

	while (Window.isOpen()) 
	{
		ProcessEvents();
		Update();
		Render();
	}
}

void ShowCase::ProcessEvents() 
{
	sf::Event Event;
	while (Window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			Window.close();
		}

		if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Left)
		{
			IsLeftMouseButtonPressed = true;
		}

		if (Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Left)
		{
			IsLeftMouseButtonPressed = false;
			TimeSinceLastSpawn = 0.0f;
		}

		if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Right)
		{
			IsRightMouseButtonPressed = true;
		}

		if (Event.type == sf::Event::MouseButtonReleased && Event.mouseButton.button == sf::Mouse::Right)
		{
			IsRightMouseButtonPressed = false;
			TimeSinceLastSpawn = 0.0f;
		}
		//TODO events for changing shapes
	}
}

void ShowCase::Update()
{
	float DeltaTime = Clock.restart().asSeconds();
	PhysicsEngine.Update(DeltaTime);
	ClearMarkedShapes();

	TryToSpawnShape(DeltaTime);

	DebugText.setString(PhysicsEngine.GetDebugInfo());
}

void ShowCase::TryToSpawnShape(float DeltaTime)
{
	if (IsLeftMouseButtonPressed)
	{
		TimeSinceLastSpawn += DeltaTime;

		if (TimeSinceLastSpawn >= ShowcaseConfig::SPAWN_COOLDOWN)
		{
			sf::Vector2i MousePosition = sf::Mouse::getPosition(Window);
			sf::Vector2f WorldCoords = Window.mapPixelToCoords(MousePosition);
			FVector2D WorldPosition(WorldCoords.x, WorldCoords.y);
			SpawnShape(WorldPosition, true);

			TimeSinceLastSpawn = 0.0f;

			return;
		}
	}

	if (IsRightMouseButtonPressed)
	{
		TimeSinceLastSpawn += DeltaTime;

		if (TimeSinceLastSpawn >= ShowcaseConfig::SPAWN_COOLDOWN)
		{
			sf::Vector2i MousePosition = sf::Mouse::getPosition(Window);
			sf::Vector2f WorldCoords = Window.mapPixelToCoords(MousePosition);
			FVector2D WorldPosition(WorldCoords.x, WorldCoords.y);
			SpawnShapeSpanwer(WorldPosition, CurrentShape);

			TimeSinceLastSpawn = 0.0f;

			return;
		}
	}
}

void ShowCase::Render() {
	Window.clear();

	DrawAllShapes();
	Window.draw(DebugText);

	Window.display();
}

void ShowCase::DrawAllShapes()
{
	for (const auto& shape : Shapes) 
	{
		if (shape) 
		{
			shape->Draw(Window);
		}
	}
}

void ShowCase::ClearMarkedShapes()
{
	for (auto it = Shapes.begin(); it != Shapes.end(); )
	{
		if (it->get()->IsMarkedForDeletion())
		{
			it = Shapes.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void ShowCase::SpawnShape(const FVector2D& Position, bool IsDynamic)
{
	switch (CurrentShape)
	{
	case EShapeType::Circle:
		SpawnCircle(ShowcaseConfig::DEFAULT_CIRCLE_RADIUS , Position, IsDynamic);
		break;

	case EShapeType::AABB:
		SpawnAABB(FVector2D(ShowcaseConfig::DEFAULT_AABB_SIZE, ShowcaseConfig::DEFAULT_AABB_SIZE), Position, IsDynamic);
		break;
	}
}

void ShowCase::SpawnShapeSpanwer(const FVector2D& Position, EShapeType Shape)
{
}

void ShowCase::SpawnCircle(float Radius, const FVector2D& Position, bool IsDynamic, sf::Color InColor)
{
	std::shared_ptr <CircleComponent> NewCircleComponent = PhysicsEngine.CreateCircle(Radius, Position);
	assert(NewCircleComponent && "Physic Circle Component failed to construct");
	NewCircleComponent->SetDynamic(IsDynamic);

	auto NewCircle = std::make_unique<Circle>(NewCircleComponent, InColor);

	Shapes.push_back(std::move(NewCircle));
}

void ShowCase::SpawnAABB(const FVector2D& Size, const FVector2D& Position, bool IsDynamic, sf::Color InColor)
{
	std::shared_ptr<AABBComponent> NewAABBComponent = PhysicsEngine.CreateAABB(Size, Position);
	assert(NewAABBComponent && "Physic AABB Component failed to construct");
	NewAABBComponent->SetDynamic(IsDynamic);

	auto NewAABB = std::make_unique<AABB>(NewAABBComponent, InColor);

	Shapes.push_back(std::move(NewAABB));
}

void ShowCase::SpawnLevel()
{
	SpawnAABB(FVector2D(500.f, 50.f), FVector2D(550.f, 700.f), false, sf::Color::Red);
}
