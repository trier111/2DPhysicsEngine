#include "Circle.h"

#include "Core/CircleComponent.h"

Circle::Circle(std::shared_ptr<CircleComponent> InCircleComponent) : PhysicalCircle(InCircleComponent.get())
{
    CircleShape.setRadius(PhysicalCircle->GetRadius());
    CircleShape.setOrigin(PhysicalCircle->GetRadius(), PhysicalCircle->GetRadius());
    CircleShape.setPosition(PhysicalCircle->GetPosition().X, PhysicalCircle->GetPosition().Y);
    CircleShape.setFillColor(sf::Color::Green);

    PhysicalCircle->AddPositionObserver(this);
    PhysicalCircle->AddDestructionObserver(this);
}

void Circle::Draw(sf::RenderWindow& window)
{
    window.draw(CircleShape);
}

void Circle::OnRigidBodyPositionUpdated(const FVector2D& NewPosition)
{
    CircleShape.setPosition(NewPosition.X, NewPosition.Y);
}
