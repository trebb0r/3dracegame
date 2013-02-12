#include <cassert>
#include <iostream>
#include "SphereCollider.hpp"
#include "../GameObject.hpp"

SphereCollider::SphereCollider( GameObject * aParent, float aRadius )
:	Collider( aParent ), radius( aRadius )
{
	//ctor
}

SphereCollider::~SphereCollider()
{
	//dtor
}

bool SphereCollider::collides( Collider * otherCollider )
{
	//std::cout << "Check CD for " << parent->getName() << std::endl;
	return otherCollider->collides( this );
}

bool SphereCollider::collides( SphereCollider * otherCollider )
{
	std::cout << "CD for " << parent->getName() << " - " << otherCollider->parent->getName() << std::endl;

	// todo
	return false;
}
