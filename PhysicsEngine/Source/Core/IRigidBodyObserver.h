#pragma once

class FVector2D;

class IRigidBodyObserver
{

public:

    virtual ~IRigidBodyObserver() = default;

    virtual void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) = 0;
};
