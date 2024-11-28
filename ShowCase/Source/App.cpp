#include <SFML/Graphics.hpp>
#include "Defines.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Physics Engine with SFML");
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color::Green);
	sf::Vector2f windowCenter(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
	shape.setPosition(windowCenter.x - shape.getRadius(), windowCenter.y - shape.getRadius());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized) 
			{
				sf::View view(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
				window.setView(view);
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}