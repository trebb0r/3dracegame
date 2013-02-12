#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include "glm.hpp"

class Texture;

class ShaderProgram
{
	public: // var locations
		GLuint id;

	public: // functions
		ShaderProgram( const char * vertexFileName, const char * fragmentFileName );
		virtual ~ShaderProgram();

		void load( const char * vertexFileName, const char * fragmentFileName ); // loads, compiles and links the shaders

		GLuint getUniformLocation( const char * name );
		GLuint getAttribLocation(  const char * name  );
		void use();

		void draw( unsigned int count );

	private: // functions
		std::string readFile( const char * filePath );
		GLuint compileShader( GLenum type, std::string & shaderCode);
		GLuint linkProgram ( GLuint vertexShaderId, GLuint fragmentShaderId );
		void getLocations();



};

#endif // SHADERPROGRAM_H

