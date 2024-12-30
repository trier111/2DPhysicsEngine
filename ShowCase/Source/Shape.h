#pragma once

#include <SFML/Graphics.hpp>
#include "Core/IRigidBodyDestructionObserver.h"

namespace sf 
{
	class RenderWindow;
}

class Shape : public IRigidBodyDestructionObserver
{
public:

	Shape();

	virtual ~Shape() {}

	virtual void Draw(sf::RenderWindow& window) = 0;

	bool IsMarkedForDeletion();

	void OnRigidBodyDestroyed() override;

protected:

	bool bMarkedForDeletion;

	void MarkForDeletion();

};

