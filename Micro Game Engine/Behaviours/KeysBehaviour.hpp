#ifndef KEYSBEHAVIOUR_H
#define KEYSBEHAVIOUR_H

#include "../Game.hpp"
#include "../Behaviour.hpp"


class KeysBehaviour : public Behaviour
{
    private:
        Game * game;
	public:
		KeysBehaviour( GameObject * aParent , Game * aGame );
		virtual ~KeysBehaviour();

		virtual void update( float step );
};

#endif // KEYSBEHAVIOUR_H
