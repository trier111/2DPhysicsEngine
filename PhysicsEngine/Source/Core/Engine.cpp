#include "Engine.h"

#include <cmath>
#include "Core/AABBComponent.h"
#include "Core/CircleComponent.h"
#include "Core/Defines.h"

Engine::Engine() :
    Gravity(0, EngineConfig::GRAVITY)
{
}

Engine& Engine::GetInstance()
{
    static Engine EngineInstance;
    return EngineInstance;
}

void Engine::Update(float DeltaTime)
{
    CheckCollisions();

    for (auto it = RigidBodies.begin(); it != RigidBodies.end(); )
    {
        auto& Body = *it;

        Body->ApplyGravity(Gravity);
        Body->Update(DeltaTime);

        if (Body->IsMarkedForDeletion())
        {
            it = RigidBodies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::shared_ptr<CircleComponent> Engine::CreateCircle(float Radius, const FVector2D& StartPosition)
{
    auto NewCircle = std::make_shared<CircleComponent>(Radius, StartPosition);
    RigidBodies.push_back(NewCircle);

    return NewCircle;
}

std::shared_ptr<AABBComponent> Engine::CreateAABB(const FVector2D& Size, const FVector2D& StartPosition)
{
    auto NewAABB = std::make_shared<AABBComponent>(Size, StartPosition);
    RigidBodies.push_back(NewAABB);

    return NewAABB;
}

void Engine::HandleCollision(CircleComponent& Circle,AABBComponent& aabb)
{
    float ClosestX = std::max(aabb.GetPosition().X, std::min(Circle.GetPosition().X, aabb.GetPosition().X + aabb.GetWidth()));
    float ClosestY = std::max(aabb.GetPosition().Y, std::min(Circle.GetPosition().Y, aabb.GetPosition().Y + aabb.GetHeight()));

    float DistanceX = Circle.GetPosition().X - ClosestX;
    float DistanceY = Circle.GetPosition().Y - ClosestY;

    float DistanceSquared = DistanceX * DistanceX + DistanceY * DistanceY;

    if (DistanceSquared <= (Circle.GetRadius() * Circle.GetRadius()))
    {
        float PenetrationDepth = Circle.GetRadius() - std::sqrt(DistanceSquared);

        FVector2D CollisionNormal = ComputeCollisionNormal(Circle.GetPosition(), FVector2D(ClosestX, ClosestY));

        ResolveCollision(Circle, aabb, CollisionNormal);

        PositionalCorrection(Circle, aabb, CollisionNormal, PenetrationDepth);
    }
}

void Engine::HandleCollision(CircleComponent& Circle1,CircleComponent& Circle2)
{
    float DistanceX = Circle1.GetPosition().X - Circle2.GetPosition().X;
    float DistanceY = Circle1.GetPosition().Y - Circle2.GetPosition().Y;
    float DistanceSquared = DistanceX * DistanceX + DistanceY * DistanceY;

    float CombinedRadius = Circle1.GetRadius() + Circle2.GetRadius();
    if (DistanceSquared <= (CombinedRadius * CombinedRadius))
    {
        float PenetrationDepth = CombinedRadius - std::sqrt(DistanceSquared);

        FVector2D CollisionNormal = ComputeCollisionNormal(Circle1.GetPosition(), Circle2.GetPosition());

        ResolveCollision(Circle1, Circle2, CollisionNormal);

        PositionalCorrection(Circle1, Circle2, CollisionNormal, PenetrationDepth);
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
        float PenetrationDepthX = std::min(aabb1.GetPosition().X + aabb1.GetWidth() - aabb2.GetPosition().X,
            aabb2.GetPosition().X + aabb2.GetWidth() - aabb1.GetPosition().X);

        float PenetrationDepthY = std::min(aabb1.GetPosition().Y + aabb1.GetHeight() - aabb2.GetPosition().Y,
            aabb2.GetPosition().Y + aabb2.GetHeight() - aabb1.GetPosition().Y);

        float PenetrationDepth = std::min(PenetrationDepthX, PenetrationDepthY);

        FVector2D CollisionNormal = ComputeCollisionNormal(aabb1.GetPosition(), aabb2.GetPosition());

        PositionalCorrection(aabb1, aabb2, CollisionNormal, PenetrationDepth);

        ResolveCollision(aabb1, aabb2, CollisionNormal);
    }
}

void Engine::CheckCollisions()
{
    for (size_t i = 0; i < RigidBodies.size(); ++i)
    {
        std::shared_ptr<RigidBodyComponent> BodyA = RigidBodies[i];

        for (size_t j = i + 1; j < RigidBodies.size(); ++j)
        {
            std::shared_ptr<RigidBodyComponent> BodyB = RigidBodies[j];

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

    float ImpulseMagnitude = -VelocityAlongNormal / (1.0f / MassA + 1.0f / MassB);

    FVector2D Impulse = CollisionNormal * ImpulseMagnitude;

    if (BodyA.IsDynamic())
    {
        BodyA.SetVelocity(BodyA.GetVelocity() + Impulse / MassA);
    }

    if (BodyB.IsDynamic())
    {
        BodyB.SetVelocity(BodyB.GetVelocity() - Impulse / MassB);
    }
}

void Engine::PositionalCorrection(RigidBodyComponent& BodyA, RigidBodyComponent& BodyB, const FVector2D& CollisionNormal, float PenetrationDepth)
{
    const float CorrectionFactor = 0.5f;
    FVector2D Correction = CollisionNormal * PenetrationDepth * CorrectionFactor;

    if (!BodyA.IsDynamic() || !BodyB.IsDynamic())
    {
        Correction = Correction * 2.f;
    }

    if (BodyA.IsDynamic())
    {
        BodyA.SetPosition(BodyA.GetPosition() + Correction);
    }

    if (BodyB.IsDynamic())
    {
        BodyB.SetPosition(BodyB.GetPosition() - Correction);
    }
}
