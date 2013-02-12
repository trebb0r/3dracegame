#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "../Behaviour.hpp"


class KeysBehaviour : public Behaviour
{
	public:
		KeysBehaviour( GameObject * aParent );
		virtual ~KeysBehaviour();

		virtual void update( float step );
};

#endif // KEYSBEHAVIOUR_H
