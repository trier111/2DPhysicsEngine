#pragma once

#include "Shape.h"
#include "Core/IRigidBodyPositionObserver.h"

class AABBComponent;

class AABB : public Shape,
	public IRigidBodyPositionObserver
{

public:

	AABB(std::shared_ptr <AABBComponent> InAABBComponent);

	void Draw(sf::RenderWindow& window) override;

	void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) override;


private:

	std::weak_ptr<AABBComponent> PhysicalAABB;

	sf::RectangleShape RectangleShape;

};
