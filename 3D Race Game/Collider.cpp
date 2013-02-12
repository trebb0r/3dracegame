#include <iostream>
#include "Collider.hpp"
#include "GameObject.hpp"

Collider::Collider( GameObject * aParent, float aRadius )
:	parent(aParent), radius( aRadius )
{
	//ctor
}

Collider::~Collider()
{
	//dtor
}

bool Collider::collides( Collider * otherCollider )
{
	//std::cout << "Check CD for " << parent->getName() << std::endl;
	glm::vec3 location = parent->getLocation();
	glm::vec3 otherLocation = otherCollider->parent->getLocation();
	float distance = glm::distance( location, otherLocation );
	if ( distance < radius + otherCollider->radius ) {
		std::cout << parent->getName() << " Hits " << otherCollider->parent->getName() << std::endl;
		return true;
	};
	return false;
}

