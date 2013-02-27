#include <cassert>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include "FPS.hpp"
#include "Hud.hpp"

Hud::Hud( sf::RenderWindow * aWindow )
:	window( aWindow )
{
	assert ( window != NULL );

    if ( marvinTex.loadFromFile("models/marvin.png") ) {
		marvin.setTexture( marvinTex);
		marvin.setPosition(150,150);
    } else {
		std::cout << "Coulf not load sprite" << std::endl;
	}
}

Hud::~Hud()
{
	//dtor
}

void Hud::draw()
{
	glDisable( GL_CULL_FACE ); // needed for text, dont know why
	char fps[] = "Test";
	sprintf( fps, "%4d", FPS::getFPS() );
	sf::Text text( fps );
	//text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::White);
	text.setPosition( 10,10);



	// Draw it
	//std::cout << "Drawing text" << std::endl;
	assert ( window != NULL );
	window->draw( marvin );
	window->draw(text);
}
