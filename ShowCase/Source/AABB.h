#pragma once

#include "Shape.h"
#include "Core/IRigidBodyObserver.h"

class AABBComponent;

class AABB : public Shape,
    public IRigidBodyObserver
{

public:

    AABB(std::shared_ptr <AABBComponent> InAABBComponent);

    void Draw(sf::RenderWindow& window) override;

    void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) override;

private:

    AABBComponent* PhysicalAABB;

    sf::RectangleShape RectangleShape;

};
