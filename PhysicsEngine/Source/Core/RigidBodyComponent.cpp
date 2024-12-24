#include "RigidBodyComponent.h"

#include "Core/Defines.h"
#include "Core/IRigidBodyObserver.h"

RigidBodyComponent::RigidBodyComponent()
    : Mass(100.0f),
    Velocity(FVector2D(0.0f, 0.0f)),
    Acceleration(FVector2D(0.0f, 0.0f)),
    bIsDynamic(true)
{
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Update(float DeltaTime)
{
    if (!bIsDynamic)
    {
        return;
    }

    Velocity += Acceleration * DeltaTime;

    Velocity = Velocity * (1.0f - EngineConfig::DAMPING_FACTOR * DeltaTime);

    Position += Velocity * DeltaTime;

    NotifyObservers();
}

void RigidBodyComponent::ApplyForce(const FVector2D& Force)
{
    if (!bIsDynamic)
    {
        return;
    }
    if (Mass < EngineConfig::EPSILON)
    {
        return;
    }

    Acceleration += Force / Mass;
}

void RigidBodyComponent::ApplyGravity(const FVector2D& Gravity)
{
    if (!bIsDynamic)
    {
        return;
    }
    if (Mass < EngineConfig::EPSILON)
    {
        return;
    }

    Acceleration += Gravity;
}

void RigidBodyComponent::NotifyObservers()
{
    for (IRigidBodyObserver* Observer : Observers)
    {
        if (Observer)
        {
            Observer->OnRigidBodyPositionUpdated(Position);
        }
    }
}

void RigidBodyComponent::AddObserver(IRigidBodyObserver* Observer)
{
    if (std::find(Observers.begin(), Observers.end(), Observer) == Observers.end())
    {
        Observers.push_back(Observer);
    }
}

void RigidBodyComponent::RemoveObserver(IRigidBodyObserver* Observer)
{
    Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer), Observers.end());
}

void RigidBodyComponent::SetMass(float InMass)
{
    Mass = InMass;
}

float RigidBodyComponent::GetMass() const
{
    return Mass;
}

FVector2D RigidBodyComponent::GetPosition() const
{
    return Position;
}

FVector2D RigidBodyComponent::GetVelocity() const
{
    return Velocity;
}

void RigidBodyComponent::SetDynamic(bool bDynamic)
{
    bIsDynamic = bDynamic;

    if (!bIsDynamic) 
    {
        Velocity = FVector2D(0.0f, 0.0f);
        Acceleration = FVector2D(0.0f, 0.0f);
    }
}

bool RigidBodyComponent::IsDynamic() const
{
    return bIsDynamic;
}
