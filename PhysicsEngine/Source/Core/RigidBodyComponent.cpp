#include "RigidBodyComponent.h"

#include "Core/Defines.h"
#include "Core/IRigidBodyPositionObserver.h"
#include "Core/IRigidBodyDestructionObserver.h"

RigidBodyComponent::RigidBodyComponent()
	: Mass(10.0f),
	Velocity(FVector2D(0.0f, 0.0f)),
	Acceleration(FVector2D(0.0f, 0.0f)),
	bIsDynamic(true),
	bMarkedForDeletion(false)
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

	Acceleration = FVector2D(0.f, 0.f);

	NotifyPositionObservers();

	if (IsOutOfBounds())
	{
		MarkForDeletion();
	}

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

void RigidBodyComponent::MarkForDeletion()
{
	bMarkedForDeletion = true;
	NotifyDestructionObservers();
}

bool RigidBodyComponent::IsOutOfBounds()
{
	return Position.Y > EngineConfig::BOTTOMBOUND;
}

void RigidBodyComponent::AddPositionObserver(IRigidBodyPositionObserver* Observer)
{
	if (std::find(PositionObservers.begin(), PositionObservers.end(), Observer) == PositionObservers.end())
	{
		PositionObservers.push_back(Observer);
	}
}

void RigidBodyComponent::RemovePositionObserver(IRigidBodyPositionObserver* Observer)
{
	PositionObservers.erase(std::remove(PositionObservers.begin(), PositionObservers.end(), Observer), PositionObservers.end());
}

void RigidBodyComponent::NotifyPositionObservers()
{
	for (IRigidBodyPositionObserver* Observer : PositionObservers)
	{
		if (Observer)
		{
			Observer->OnRigidBodyPositionUpdated(Position);
		}
	}
}

void RigidBodyComponent::AddDestructionObserver(IRigidBodyDestructionObserver* Observer)
{
	if (std::find(DestructionObservers.begin(), DestructionObservers.end(), Observer) == DestructionObservers.end())
	{
		DestructionObservers.push_back(Observer);
	}
}

void RigidBodyComponent::RemoveDestructionObserver(IRigidBodyDestructionObserver* Observer)
{
	DestructionObservers.erase(std::remove(DestructionObservers.begin(), DestructionObservers.end(), Observer), DestructionObservers.end());
}

void RigidBodyComponent::NotifyDestructionObservers()
{
	for (IRigidBodyDestructionObserver* Observer : DestructionObservers)
	{
		if (Observer)
		{
			Observer->OnRigidBodyDestroyed();
		}
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

void RigidBodyComponent::SetPosition(const FVector2D& NewPosition)
{
	Position = NewPosition;

	NotifyPositionObservers();
}

FVector2D RigidBodyComponent::GetVelocity() const
{
	return Velocity;
}

FVector2D RigidBodyComponent::GetPosition() const
{
	return Position;
}

void RigidBodyComponent::SetVelocity(const FVector2D& NewVelocity)
{
	Velocity = NewVelocity;
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

bool RigidBodyComponent::IsMarkedForDeletion()
{
	return bMarkedForDeletion;
}
