#pragma once

#include "Shape.h"
#include "Core/IRigidBodyPositionObserver.h"
#include "ColorUtils.h"

class CircleComponent;

class Circle : public Shape,
	public IRigidBodyPositionObserver
{

public:

	Circle(std::shared_ptr<CircleComponent> InCircleComponent, sf::Color InColor);

	void Draw(sf::RenderWindow& window) override;

	void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) override;

private:

	std::weak_ptr<CircleComponent> PhysicalCircle;

	sf::CircleShape CircleShape;
};

