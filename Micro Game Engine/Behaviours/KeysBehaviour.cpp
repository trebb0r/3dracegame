#include "KeysBehaviour.hpp"
#include <SFML/Window.hpp>

#include "../GameObject.hpp"

KeysBehaviour::KeysBehaviour( GameObject * aParent, Game * aGame )
:	Behaviour( aParent ), game( aGame )
{
}

KeysBehaviour::~KeysBehaviour()
{
}

void KeysBehaviour::update( float step )
{
	float speed = 0.0f; //default if no keys
	float rotationSpeed = 0.0f;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
		speed = 10.0f;
		//transformation =  glm::translate( transformation, glm::vec3(0.0f, 0.0f, -10.0f*step ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
		speed = -10.0f;
		//transformation =  glm::translate( transformation, glm::vec3(0.0f, 0.0f, 10.0f*step ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
		rotationSpeed = -135.0f;
		//transformation = glm::rotate( transformation, -135*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
		rotationSpeed = +135.0f;
		//transformation = glm::rotate( transformation, 135*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape )){
        //close window
        game->stop();
	}
	parent->translate( glm::vec3(0.0f, 0.0f, speed*step ) );
	parent->rotate( rotationSpeed*step, glm::vec3(0.0f, 1.0f, 0.0f ) );
//	transformation = glm::translate( transformation, glm::vec3(0.0f, 0.0f, speed*step ) );
//	transformation = glm::rotate( transformation, rotationSpeed*step, glm::vec3(0.0f, 1.0f, 0.0f ) );

}
