#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <map>
#include <GL/glew.h>

class Mesh;
class ShaderProgram;

class Texture
{
	private:
		const char * name;
		GLuint id; // OpenGL id for texture buffer
		static std::map< const char *, Texture * > textures; //all previously loaded meshes;

	private:
		Texture( const char * aName );

	public:
		static Texture * load( const char * aName );
		virtual ~Texture();

		GLuint getId();

};

#endif // TEXTURE_H
