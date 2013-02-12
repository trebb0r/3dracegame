#ifndef WASDBEHAVIOUR_H
#define WASDBEHAVIOUR_H

#include <SFML/Window.hpp>
#include "../Behaviour.hpp"


class WASDBehaviour : public Behaviour
{
	private:
		sf::Window * window;

	public:
		WASDBehaviour( GameObject * aParent, sf::Window * aWindow );
		virtual ~WASDBehaviour();

		virtual void update( float step );
};

#endif // WASDBEHAVIOUR_H
