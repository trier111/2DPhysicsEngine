#include "Engine.h"

#include "Core/AABBComponent.h"
#include "Core/CircleComponent.h"
#include "Core/Defines.h"

Engine::Engine() :
    Gravity(0, EngineConfig::GRAVITY)
{
}

void Engine::Update(float DeltaTime)
{
    CheckCollisions();

    for (auto* Body : RigidBodies)
    {
        Body->ApplyGravity(Gravity);

        Body->Update(DeltaTime);
    }
}

CircleComponent* Engine::CreateCircle(float Radius, const FVector2D& StartPosition)
{
    CircleComponent* NewCircle = new CircleComponent(Radius, StartPosition);
    RigidBodies.push_back(NewCircle);

    return NewCircle;
}

AABBComponent* Engine::CreateAABB(const FVector2D& Size, const FVector2D& StartPosition)
{
    AABBComponent* NewAABB = new AABBComponent(Size, StartPosition);
    RigidBodies.push_back(NewAABB);

    return NewAABB;
}

void Engine::HandleCollision(CircleComponent& Circle,AABBComponent& aabb)
{
    float ClosestX = std::max(aabb.GetPosition().X, std::min(Circle.GetPosition().X, aabb.GetPosition().X + aabb.GetWidth()));
    float ClosestY = std::max(aabb.GetPosition().Y, std::min(Circle.GetPosition().Y, aabb.GetPosition().Y + aabb.GetHeight()));

    float DistanceX = Circle.GetPosition().X - ClosestX;
    float DistanceY = Circle.GetPosition().Y - ClosestY;

    if ((DistanceX * DistanceX + DistanceY * DistanceY) <= (Circle.GetRadius() * Circle.GetRadius()))
    {
        FVector2D CollisionNormal = ComputeCollisionNormal(Circle.GetPosition(), FVector2D(ClosestX, ClosestY));

        ResolveCollision(Circle, aabb, CollisionNormal);
    }
}

void Engine::HandleCollision(CircleComponent& Circle1,CircleComponent& Circle2)
{
    float distanceX = Circle1.GetPosition().X - Circle2.GetPosition().X;
    float distanceY = Circle1.GetPosition().Y - Circle2.GetPosition().Y;
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;

    float combinedRadius = Circle1.GetRadius() + Circle2.GetRadius();
    if (distanceSquared <= (combinedRadius * combinedRadius))
    {
        FVector2D CollisionNormal = ComputeCollisionNormal(Circle1.GetPosition(), Circle2.GetPosition());

        ResolveCollision(Circle1, Circle2, CollisionNormal);
    }
}

void Engine::HandleCollision(AABBComponent& aabb1,AABBComponent& aabb2)
{
    const bool isOverlappingX = aabb1.GetPosition().X < aabb2.GetPosition().X + aabb2.GetWidth() &&
        aabb1.GetPosition().X + aabb1.GetWidth() > aabb2.GetPosition().X;

    const bool isOverlappingY = aabb1.GetPosition().Y < aabb2.GetPosition().Y + aabb2.GetHeight() &&
        aabb1.GetPosition().Y + aabb1.GetHeight() > aabb2.GetPosition().Y;

    if (isOverlappingX && isOverlappingY)
    {
        FVector2D CollisionNormal = ComputeCollisionNormal(aabb1.GetPosition(), aabb2.GetPosition());

        ResolveCollision(aabb1, aabb2, CollisionNormal);
    }
}

void Engine::CheckCollisions()
{
    for (size_t i = 0; i < RigidBodies.size(); ++i)
    {
        RigidBodyComponent* BodyA = RigidBodies[i];

        for (size_t j = i + 1; j < RigidBodies.size(); ++j)
        {
            RigidBodyComponent* BodyB = RigidBodies[j];

            BodyA->CheckCollision(*BodyB);
        }
    }
}

FVector2D Engine::ComputeCollisionNormal(const FVector2D& PositionA, const FVector2D& PositionB)
{
    FVector2D Normal = PositionA - PositionB;
    Normal = Normal.Normalized();
    return Normal;
}

void Engine::ResolveCollision(RigidBodyComponent& BodyA, RigidBodyComponent& BodyB, const FVector2D& CollisionNormal)
{
    if (!BodyA.IsDynamic() && !BodyB.IsDynamic())
    {
        return;
    }

    float MassA = BodyA.IsDynamic() ? BodyA.GetMass() : FLT_MAX;
    float MassB = BodyB.IsDynamic() ? BodyB.GetMass() : FLT_MAX;

    FVector2D RelativeVelocity = BodyA.GetVelocity() - BodyB.GetVelocity();

    float VelocityAlongNormal = RelativeVelocity.Dot(CollisionNormal);

    if (VelocityAlongNormal > 0)
    {
        return;
    }

    float Impulse = -(2.0f * VelocityAlongNormal) / (1.0f / MassA + 1.0f / MassB);

    FVector2D ImpulseVector = CollisionNormal * Impulse;

    if (BodyA.IsDynamic())
    {
        BodyA.ApplyForce(ImpulseVector);
    }

    if (BodyB.IsDynamic())
    {
        BodyB.ApplyForce(ImpulseVector * -1);
    }
}

