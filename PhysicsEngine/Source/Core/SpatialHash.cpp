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

void SpatialHashComponent::Insert(const FVector2D& Position, const FVector2D& Size, RigidBodyComponent* RigidBody)
{
    unsigned int centralKey = Key(Position);
    RigidBodyToCell[RigidBody] = centralKey;

    if (Size.X <= CellSize && Size.Y <= CellSize)
    {
        ÑellToRigidBodies[centralKey].push_back(RigidBody);
    }
    else
    {
        int MinX = static_cast<int>(std::floor((Position.X - Size.X / 2) / CellSize));
        int MaxX = static_cast<int>(std::floor((Position.X + Size.X / 2) / CellSize));
        int MinY = static_cast<int>(std::floor((Position.Y - Size.Y / 2) / CellSize));
        int MaxY = static_cast<int>(std::floor((Position.Y + Size.Y / 2) / CellSize));

        for (int x = MinX; x <= MaxX; ++x)
        {
            for (int y = MinY; y <= MaxY; ++y)
            {
                unsigned int key = (x << XSHIFT) | (y << YSHIFT);
                ÑellToRigidBodies[key].push_back(RigidBody);
            }
        }
    }
}

std::vector<RigidBodyComponent*> SpatialHashComponent::QueryPosition(const FVector2D& Position, const FVector2D& Size) const
{
    std::vector<RigidBodyComponent*> Result;

    int MinX = static_cast<int>(std::floor((Position.X - Size.X / 2) / CellSize));
    int MaxX = static_cast<int>(std::floor((Position.X + Size.X / 2) / CellSize));
    int MinY = static_cast<int>(std::floor((Position.Y - Size.Y / 2) / CellSize));
    int MaxY = static_cast<int>(std::floor((Position.Y + Size.Y / 2) / CellSize));

    for (int x = MinX - 1; x <= MaxX + 1; ++x)
    {
        for (int y = MinY - 1; y <= MaxY + 1; ++y)
        {
            unsigned int NeighborKey = (x << XSHIFT) | (y << YSHIFT);

            auto it = ÑellToRigidBodies.find(NeighborKey);
            if (it != ÑellToRigidBodies.end())
            {
                Result.insert(Result.end(), it->second.begin(), it->second.end());
            }
        }
    }

    return Result;
}

bool SpatialHashComponent::ContainsKey(const FVector2D& Position) const
{
    return ÑellToRigidBodies.find(Key(Position)) != ÑellToRigidBodies.end();
}

void SpatialHashComponent::Clear()
{
    ÑellToRigidBodies.clear();
    RigidBodyToCell.clear();
}