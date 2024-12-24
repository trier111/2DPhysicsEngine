#include "AABBComponent.h"

#include "Core/Engine.h"

AABBComponent::AABBComponent(const FVector2D& InSize, const FVector2D& StartPosition) : Size(InSize)
{
	Position = StartPosition;
}

void AABBComponent::CheckCollision(RigidBodyComponent& other)
{
	other.CheckCollision(*this);
}

void AABBComponent::CheckCollision(CircleComponent& other)
{
	Engine::HandleCollision(other, *this);
}

void AABBComponent::CheckCollision(AABBComponent& other)
{
	Engine::HandleCollision(*this, other);
}
