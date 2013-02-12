#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "glm.hpp"

class ShaderProgram;
class Texture;

class Renderer
{
	private:
		sf::Window * window;

		// the shader wrapper
		ShaderProgram * program;
		// shader input locations
		GLuint projectionLoc, viewLoc, modelLoc, lightLoc, timeLoc; 	// uniform locations
		GLuint verticesLoc, normalsLoc, uvsLoc;		// attribute locations
		GLuint colorMapLoc;

		// buffered variables
		float time;
		glm::mat4 projection, view, model;
		glm::vec3 light;
		GLuint colorMap;

	public:
		Renderer( sf::Window * aWindow );
		virtual ~Renderer();

		void use( ShaderProgram * program );

		void clear( glm::vec4 backgroundColor );

			void setProjection( glm::mat4 aProjection );
			void setView( glm::mat4 aView );
			void setModel( glm::mat4 aModel );

			void setTime( float aTime );
			void setLight( glm::vec3 aLight );
			void setColorMap ( Texture * aColorMap );

			// attributes for drawElements so indexed drawing
			void draw( unsigned int size, GLuint indicesId, GLuint verticesId, GLuint normalsId, GLuint uvsId );

		void display();

	private:
		void findLocations();
};

#endif // RENDERER_H
