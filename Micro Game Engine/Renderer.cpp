#include "Renderer.hpp"
#include <cassert>
#include <GL/glew.h>

#include "Time.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"

Renderer::Renderer( sf::Window * aWindow )
:	window( aWindow ), program( NULL )
{
}

Renderer::~Renderer()
{
	delete program;
}

void Renderer::use( ShaderProgram * aProgram )
{
	program = aProgram;
	program->use(); // this is the default program
	findLocations(); // find where to put the uniforms to
}

void Renderer::setProjection( glm::mat4 aProjection )
{
	projection = aProjection; // cache P matrix
}

void Renderer::setView( glm::mat4 aView )
{
	view = aView; // cache V matrix
}

void Renderer::setModel( glm::mat4 aModel )
{
	model = aModel; // cache M matrix
}

void Renderer::setLight( glm::vec3 aLight )
{
	light = aLight; // cache light prosition for positional light
}

void Renderer::setColorMap( Texture * aColorMap ) // for single texture at a time, otherwise use activeTexture
{
	colorMap = aColorMap->getId();
}

void Renderer::setTime( float aTime )
{
	time = aTime; // set time for use in vs and fs
}

void Renderer::draw( GameObject * aWorld )
{
	program->use(); // make sure default shader program is used
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE ); // defaul GL_BACK
	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear screen 0
	time = Time::now(); // provide the shader with time float in seconds, for later use !
	aWorld->draw( this );
}

void Renderer::draw( unsigned int size, GLuint indicesBuffer, GLuint verticesBuffer, GLuint normalsBuffer, GLuint uvsBuffer ) // size is count of indices
{
	// set all uniforms
	glUniform1f ( timeLoc, time );
	glUniformMatrix4fv ( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );
	glUniformMatrix4fv ( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv ( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
	glUniform3fv ( lightLoc, 1, glm::value_ptr( light ) );
	glBindTexture( GL_TEXTURE_2D, colorMap );
	glUniform1i ( colorMapLoc, 0 );

	// set attributes
	// set indices attribute
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer );
	// set vertexattribute
	glEnableVertexAttribArray( verticesLoc ); // enable variable
	glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer ); // make vertices the current buffer
	glVertexAttribPointer( verticesLoc, 3, GL_FLOAT, GL_FALSE, 0, 0 ); // point to bound buffer
	// set normalAttribute
	glEnableVertexAttribArray( normalsLoc);
	glBindBuffer( GL_ARRAY_BUFFER, normalsBuffer ); // make vertices the current buffer
	glVertexAttribPointer( normalsLoc, 3, GL_FLOAT, GL_TRUE, 0, 0 ); // GL_TRUE for nomalisation
	// set uv attribute
	glEnableVertexAttribArray( uvsLoc );
	glBindBuffer( GL_ARRAY_BUFFER, uvsBuffer ); // make vertices the current buffer
	glVertexAttribPointer( uvsLoc, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	// draw indexed arrays
	glDrawElements( GL_TRIANGLES, size, GL_UNSIGNED_INT, (GLvoid*)0 );
	// no current buffer, to avoid mishaps
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glDisableVertexAttribArray( uvsLoc );
	glDisableVertexAttribArray( normalsLoc );
	glDisableVertexAttribArray( verticesLoc );
	glBindTexture( GL_TEXTURE_2D, 0 );
}


/*********************************************************************************/

// private members
void Renderer::findLocations()
{
	assert ( program != NULL ); // only if there is a program set

	projectionLoc 	= program->getUniformLocation( "projection" );
	viewLoc			= program->getUniformLocation( "view" );
	modelLoc 		= program->getUniformLocation( "model" );
	lightLoc 		= program->getUniformLocation( "light" );
	timeLoc			= program->getUniformLocation( "time" );
	colorMapLoc		= program->getUniformLocation( "colorMap" );

	verticesLoc		= program->getAttribLocation( "vertex" );
	normalsLoc		= program->getAttribLocation( "normal" );
	uvsLoc 			= program->getAttribLocation( "uv" );
}
