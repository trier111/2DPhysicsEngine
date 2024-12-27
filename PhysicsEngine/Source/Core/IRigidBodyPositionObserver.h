#pragma once

class FVector2D;

class IRigidBodyPositionObserver
{

public:

    virtual void OnRigidBodyPositionUpdated(const FVector2D& NewPosition) = 0;

};
