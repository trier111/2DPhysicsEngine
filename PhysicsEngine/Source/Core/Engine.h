#pragma once

#include <vector>
#include <memory>
#include "Core/FVector2D.h"

class RigidBodyComponent;
class CircleComponent;
class AABBComponent;

class Engine
{
public:

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	static Engine& GetInstance();

public:

	void Update(float DeltaTime);

	std::shared_ptr<CircleComponent> CreateCircle(float Radius, const FVector2D& StartPosition);

	std::shared_ptr<AABBComponent> CreateAABB(const FVector2D& Size, const FVector2D& StartPosition);

public:

	static void HandleCollision(CircleComponent& Circle, AABBComponent& aabb);

	static void HandleCollision(CircleComponent& Ñircle1,CircleComponent& Ñircle2);

	static void HandleCollision(AABBComponent& aabb1,AABBComponent& aabb2);

private:

	Engine();

private:

	void CheckCollisions();

	static FVector2D ComputeCollisionNormal(const FVector2D& PositionA, const FVector2D& PositionB);

	static void ResolveCollision(RigidBodyComponent& BodyA, RigidBodyComponent& BodyB, const FVector2D& CollisionNormal);

	static void PositionalCorrection(RigidBodyComponent& BodyA, RigidBodyComponent& BodyB, const FVector2D& CollisionNormal, float PenetrationDepth);


private:

	std::vector<std::shared_ptr<RigidBodyComponent>> RigidBodies;

	FVector2D Gravity;

};

