#include <cassert>
#include <iostream>
#include "Behaviour.hpp"

Behaviour::Behaviour( GameObject * aParent )
:	parent( aParent )
{
}

Behaviour::~Behaviour()
{
	//dtor
}

void Behaviour::update( float step )
{
	std::cout << "Behavour handles update. Should not be ! " << std::endl;
}
void Behaviour::onCollision( GameObject * otherGameObject )
{
	std::cout << "Behavour handles collision. Should not be ! " << std::endl;
}
