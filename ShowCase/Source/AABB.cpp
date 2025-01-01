#include "AABB.h"

#include "Core/AABBComponent.h"
#include "ColorUtils.h"

AABB::AABB(std::shared_ptr <AABBComponent> InAABBComponent) : 
	PhysicalAABB(InAABBComponent)
{
	if (auto PhysicalAABBShared = PhysicalAABB.lock())
	{
		RectangleShape.setSize(sf::Vector2f(PhysicalAABBShared->GetWidth(), PhysicalAABBShared->GetHeight()));
		RectangleShape.setOrigin(0, 0);
		RectangleShape.setPosition(PhysicalAABBShared->GetPosition().X, PhysicalAABBShared->GetPosition().Y);
		RectangleShape.setFillColor(ColorUtils::GetRandomPresetColor());

		PhysicalAABBShared->AddPositionObserver(this);
		PhysicalAABBShared->AddDestructionObserver(this);
	}
}

void AABB::Draw(sf::RenderWindow& window)
{
	window.draw(RectangleShape);
}

void AABB::OnRigidBodyPositionUpdated(const FVector2D& NewPosition)
{
	RectangleShape.setPosition(NewPosition.X, NewPosition.Y);
}
