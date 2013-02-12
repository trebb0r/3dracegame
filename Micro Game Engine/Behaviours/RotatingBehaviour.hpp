#ifndef RARTATINGBEHAVIOUR_H
#define RARTATINGBEHAVIOUR_H

#include "../Behaviour.hpp"

class RotatingBehaviour : public Behaviour
{
	public:
		RotatingBehaviour( GameObject * aParent );
		virtual ~RotatingBehaviour();

		virtual void update( float step );

};

#endif // RARTATINGBEHAVIOUR_H
