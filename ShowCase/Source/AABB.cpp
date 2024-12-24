#include "AABB.h"

#include "Core/AABBComponent.h"

AABB::AABB(AABBComponent* InAABBComponent) : PhysicalAABB(InAABBComponent)
{
    RectangleShape.setSize(sf::Vector2f(PhysicalAABB->GetWidth(), PhysicalAABB->GetHeight()));
    RectangleShape.setOrigin(PhysicalAABB->GetWidth() / 2, PhysicalAABB->GetHeight() / 2);
    RectangleShape.setPosition(PhysicalAABB->GetPosition().X, PhysicalAABB->GetPosition().Y);
    RectangleShape.setFillColor(sf::Color::Red);

    PhysicalAABB->AddObserver(this);
}

void AABB::Draw(sf::RenderWindow& window)
{
    window.draw(RectangleShape);
}

void AABB::OnRigidBodyPositionUpdated(const FVector2D& NewPosition)
{
    RectangleShape.setPosition(NewPosition.X, NewPosition.Y);
}
