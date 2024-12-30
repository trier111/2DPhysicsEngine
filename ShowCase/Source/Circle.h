#pragma once

#include "Shape.h"
#include "Core/IRigidBodyPositionObserver.h"

class CircleComponent;

class Circle : public Shape,
    public IRigidBodyPositionObserver
{

public:

    Circle(std::shared_ptr<CircleComponent> InCircleComponent);

    void Draw(sf::RenderWindow& window) override;

    void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) override;

private:

    std::weak_ptr<CircleComponent> PhysicalCircle;

    sf::CircleShape CircleShape;
};

