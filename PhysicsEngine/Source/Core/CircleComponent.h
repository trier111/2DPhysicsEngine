#pragma once

#include "RigidBodyComponent.h"

class CircleComponent : public RigidBodyComponent
{

public:

	CircleComponent(float InRadius,const FVector2D& StartPosition);

	virtual ~CircleComponent() {}

public:

	void CheckCollision(RigidBodyComponent& other) override;

	void CheckCollision(CircleComponent& other) override;

	void CheckCollision(AABBComponent& other) override;


public:

	float GetRadius() const { return Radius; }

	FVector2D GetPosition() const override;

	FVector2D GetSize() const override;

private:

	float Radius;

};

