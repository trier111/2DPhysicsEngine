#include "ShowCase.h"
#include "Defines.h"
#include <string>
#include <sstream>
#include <cassert>

ShowCase::ShowCase()
: Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Showcase with Physics Engine")
{
    Window.setFramerateLimit(MAX_FPS);

    bool FontLoaded = Font.loadFromFile("../Fonts/PressStart2P-Regular.ttf");
    assert(FontLoaded && "Font failed to load!");

    DebugText.setFont(Font);
    DebugText.setCharacterSize(16);
    DebugText.setFillColor(sf::Color::Green);
    DebugText.setPosition(10.f, 10.f);
}

void ShowCase::Run() 
{
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
    }
}

void ShowCase::Update()
{
    float deltaTime = Clock.restart().asSeconds();
    PhysicsEngine.update(deltaTime);

    std::ostringstream ss;
    ss << "Delta Time: " << deltaTime;
    DebugText.setString(ss.str());
}

void ShowCase::Render() {
    Window.clear();

    Window.draw(DebugText);

    Window.display();
}
