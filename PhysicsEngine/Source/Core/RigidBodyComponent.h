#pragma once

#include "Core/FVector2D.h"
#include <vector>

class IRigidBodyObserver;
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

    void SetMass(float Mass);

    float GetMass() const;

    FVector2D GetPosition() const;

    void SetDynamic(bool bDynamic);

    bool IsDynamic() const;

public:

    virtual void CheckCollision(RigidBodyComponent& other) = 0;
    virtual void CheckCollision(CircleComponent& other) = 0;
    virtual void CheckCollision(AABBComponent& other) = 0;

public:

    void AddObserver(IRigidBodyObserver* Observer);
    void RemoveObserver(IRigidBodyObserver* Observer);

protected:

    float Mass;

    FVector2D Velocity;

    FVector2D Acceleration;

    FVector2D Position;

    bool bIsDynamic;

private:

    void NotifyObservers();

private:

    std::vector<IRigidBodyObserver*> Observers;

};

