#pragma once

#include "Core/FVector2D.h"

class RigidBodyComponent
{

public:

    RigidBodyComponent();

    virtual ~RigidBodyComponent();

public:

    void ApplyForce(const FVector2D& Force);

    virtual void Update(float DeltaTime);

    FVector2D GetVelocity() const;

    void SetMass(float Mass);

    float GetMass() const;

protected:

    float Mass;

    FVector2D Velocity;

    FVector2D Acceleration;

};

