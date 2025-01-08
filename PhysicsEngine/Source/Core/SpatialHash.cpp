#include "Core/SpatialHash.h"

#include "Core/FVector2D.h"
#include "Core/RigidBodyComponent.h"

SpatialHashComponent::SpatialHashComponent(int InitialCellSize) :
    CellSize(InitialCellSize),
    XSHIFT(16),
    YSHIFT(0)
{
}

unsigned int SpatialHashComponent::Key(const FVector2D& Position) const
{
    unsigned int X = static_cast<unsigned int>(std::floor(Position.X / CellSize));
    unsigned int Y = static_cast<unsigned int>(std::floor(Position.Y / CellSize));

    return (X << XSHIFT) | (Y << YSHIFT);
}

void SpatialHashComponent::Insert(const FVector2D& Position, RigidBodyComponent* RigidBody)
{
    auto key = Key(Position);

    �ellToRigidBodies[key].push_back(RigidBody);
    RigidBodyToCell[RigidBody] = key;
}

void SpatialHashComponent::UpdatePosition(const FVector2D& Position, RigidBodyComponent* RigidBody)
{
    if (RigidBodyToCell.find(RigidBody) != RigidBodyToCell.end())
    {
        auto key = RigidBodyToCell[RigidBody];
        auto& vec = �ellToRigidBodies[key];
        vec.erase(std::remove(vec.begin(), vec.end(), RigidBody), vec.end());
    }

    Insert(Position, RigidBody);
}

std::vector<RigidBodyComponent*> SpatialHashComponent::QueryPosition(const FVector2D& Position) const
{
    std::vector<RigidBodyComponent*> Result;

    unsigned int baseKey = Key(Position);

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            unsigned int NeighborKey = baseKey + (dx << XSHIFT) + (dy << YSHIFT);

            auto it = �ellToRigidBodies.find(NeighborKey);
            if (it != �ellToRigidBodies.end())
            {
                Result.insert(Result.end(), it->second.begin(), it->second.end());
            }
        }
    }

    return Result;
}

bool SpatialHashComponent::ContainsKey(const FVector2D& Position) const
{
    return �ellToRigidBodies.find(Key(Position)) != �ellToRigidBodies.end();
}

void SpatialHashComponent::Clear()
{
    �ellToRigidBodies.clear();
    RigidBodyToCell.clear();
}