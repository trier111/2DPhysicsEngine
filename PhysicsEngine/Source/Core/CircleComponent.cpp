#include "CircleComponent.h"

#include "Core/Engine.h"
#include "Core/FVector2D.h"

CircleComponent::CircleComponent(float InRadius,const FVector2D& StartPosition) : Radius(InRadius)
{
    Position = StartPosition;
}

void CircleComponent::CheckCollision(RigidBodyComponent& other)
{
    other.CheckCollision(*this);
}

void CircleComponent::CheckCollision(CircleComponent& other)
{
    Engine::HandleCollision(*this, other);
}

void CircleComponent::CheckCollision(AABBComponent& other)
{
    Engine::HandleCollision(*this, other);
}
