#pragma once

#include <unordered_map>
#include <vector>

class RigidBodyComponent;
class FVector2D;

class SpatialHashComponent
{

public:
    SpatialHashComponent(int InitialCellSize);

    void Insert(const FVector2D& Position, const FVector2D& Size, RigidBodyComponent* RigidBody);

    std::vector<RigidBodyComponent*> QueryPosition(const FVector2D& Position, const FVector2D& Size) const;

    bool ContainsKey(const FVector2D& Position) const;

    void Clear();

private:

    std::unordered_map<unsigned int, std::vector<RigidBodyComponent*>> ÑellToRigidBodies;
    std::unordered_map<RigidBodyComponent*, unsigned int> RigidBodyToCell;

    int CellSize;

    unsigned int Key(const FVector2D& Position) const;

    const int XSHIFT;
    const int YSHIFT;
};

