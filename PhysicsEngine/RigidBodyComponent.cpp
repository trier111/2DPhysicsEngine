#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent()
    : Mass(1.0f), Velocity(FVector2D(0.0f, 0.0f)), Acceleration(FVector2D(0.0f, 0.0f))
{
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Update(float DeltaTime)
{
    Velocity += Acceleration * DeltaTime;
}

void RigidBodyComponent::ApplyForce(const FVector2D& Force)
{
    if (Mass != 0.0f)
    {
        Acceleration = Force / Mass;
    }
}

void RigidBodyComponent::SetMass(float InMass)
{
    Mass = InMass;
}

float RigidBodyComponent::GetMass() const
{
    return Mass;
}

FVector2D RigidBodyComponent::GetVelocity() const
{
    return Velocity;
}
