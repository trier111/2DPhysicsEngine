#pragma once

class FVector2D;

class IRigidBodyDestructionObserver
{

public:

	virtual void OnRigidBodyDestroyed() = 0;

};