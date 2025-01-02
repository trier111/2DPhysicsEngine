#include "Circle.h"

#include "Core/CircleComponent.h"

Circle::Circle(std::shared_ptr<CircleComponent> InCircleComponent, sf::Color InColor)
	: PhysicalCircle(InCircleComponent)
{
	if (auto PhysicalCircleShared = PhysicalCircle.lock()) 
	{
		CircleShape.setRadius(PhysicalCircleShared->GetRadius());
		CircleShape.setOrigin(PhysicalCircleShared->GetRadius(), PhysicalCircleShared->GetRadius());
		CircleShape.setPosition(PhysicalCircleShared->GetPosition().X, PhysicalCircleShared->GetPosition().Y);
		CircleShape.setFillColor(InColor);

		PhysicalCircleShared->AddPositionObserver(this);
		PhysicalCircleShared->AddDestructionObserver(this);
	}
}


void Circle::Draw(sf::RenderWindow& window)
{
	window.draw(CircleShape);
}

void Circle::OnRigidBodyPositionUpdated(const FVector2D& NewPosition)
{
	CircleShape.setPosition(NewPosition.X, NewPosition.Y);
}
