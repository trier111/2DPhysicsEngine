#pragma once

#include "Core/FVector2D.h"
#include <vector>

class IRigidBodyPositionObserver;
class IRigidBodyDestructionObserver;
class CircleComponent;
class AABBComponent;

class RigidBodyComponent
{

public:

	RigidBodyComponent();

	virtual ~RigidBodyComponent();

public:

	void ApplyForce(const FVector2D& Force);

	virtual void Update(float DeltaTime);

	void ApplyGravity(const FVector2D& Gravity);

public:

	FVector2D GetVelocity() const;

	void SetVelocity(const FVector2D& NewVelocity);

	void SetMass(float Mass);

	float GetMass() const;

	FVector2D GetPosition() const;

	void SetPosition(const FVector2D& NewPosition);

	void SetDynamic(bool bDynamic);

	bool IsDynamic() const;

	bool IsMarkedForDeletion();

public:

	virtual void CheckCollision(RigidBodyComponent& other) = 0;
	virtual void CheckCollision(CircleComponent& other) = 0;
	virtual void CheckCollision(AABBComponent& other) = 0;

public:

	void AddPositionObserver(IRigidBodyPositionObserver* Observer);
	void RemovePositionObserver(IRigidBodyPositionObserver* Observer);

	void AddDestructionObserver(IRigidBodyDestructionObserver* Observer);
	void RemoveDestructionObserver(IRigidBodyDestructionObserver* Observer);

protected:

	float Mass;

	FVector2D Velocity;

	FVector2D Acceleration;

	FVector2D Position;

	bool bIsDynamic;

private:

	void MarkForDeletion();

	void NotifyPositionObservers();
	void NotifyDestructionObservers();

	bool IsOutOfBounds();

private:

	std::vector<IRigidBodyPositionObserver*> PositionObservers;
	std::vector<IRigidBodyDestructionObserver*> DestructionObservers;

	bool bMarkedForDeletion;

};

