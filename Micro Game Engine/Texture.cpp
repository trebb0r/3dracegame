#include <SFML/Graphics.hpp>

#include "ShaderProgram.hpp"
#include "Texture.hpp"


std::map< const char *, Texture * > Texture::textures; // for static texturs var

Texture::Texture( const char * aName )
:	name( aName )
{
	//ctor
}

Texture::~Texture()
{
	glDeleteTextures( 1, &id ); // frees gpu memory
}


// importer for textures
Texture * Texture::load( const char * aName )
{
	// check if in cache
	std::map< const char *, Texture * >::iterator textureIterator = textures.find( aName );
	if ( textureIterator != textures.end() ) {
		std::cout << "Done loading texture form cache " << aName << std::endl;
		return textureIterator->second;// key 2 exists, do something with iter->second (the value)
	} else { // load from file and store in cache
		sf::Image image;
		if ( image.loadFromFile( aName ) ) {
			image.flipVertically();
			Texture * texture = new Texture( aName );
				glGenTextures( 1, &texture->id );
				glBindTexture( GL_TEXTURE_2D, texture->id );
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
				//glGenerateMipmap( GL_TEXTURE_2D ); 							// for mipmapping
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 ); 	// for mipmapping
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4 ); 	// for mipmapping

				std::cout << "Done loading texture " << aName << " with id " << texture->id << std::endl;
			textures[aName] = texture; // stores mesh in cache for reuse
			return texture;
		} else {
			std::cout << "Error loading texture image " << aName << std::endl;
			return NULL;
		}
	}
}


GLuint Texture::getId() {
	return id;
}



