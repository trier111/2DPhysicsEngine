#include "Shape.h"

Shape::Shape() :
	bMarkedForDeletion(false)
{
}

bool Shape::IsMarkedForDeletion()
{
	return bMarkedForDeletion;
}

void Shape::OnRigidBodyDestroyed()
{
	MarkForDeletion();
}

void Shape::MarkForDeletion()
{
	bMarkedForDeletion = true;
}
