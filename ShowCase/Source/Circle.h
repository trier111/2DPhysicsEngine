#pragma once

#include "Shape.h"
#include "Core/IRigidBodyObserver.h"

class CircleComponent;

class Circle : public Shape,
    public IRigidBodyObserver
{

public:

    Circle(CircleComponent* InCircleComponent);

    void Draw(sf::RenderWindow& window) override;

    void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) override;

private:

    CircleComponent* PhysicalCircle;

    sf::CircleShape CircleShape;
};

