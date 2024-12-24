#pragma once

#include "RigidBodyComponent.h"


class AABBComponent : public RigidBodyComponent
{

public:

    AABBComponent(const FVector2D& InSize, const FVector2D& StartPosition);

    virtual ~AABBComponent() {}

public:

    float GetWidth() const { return Size.X; }
    float GetHeight() const { return Size.Y; }

    float GetArea() const { return Size.X * Size.Y; }

public:

    void CheckCollision(RigidBodyComponent& other) override;

    void CheckCollision(CircleComponent& other) override;

    void CheckCollision(AABBComponent& other) override;

private:

    FVector2D Size;

};

