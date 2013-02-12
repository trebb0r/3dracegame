#include "ShaderProgram.hpp"

#include <iostream>
#include <fstream>

#include "Texture.hpp"

ShaderProgram::ShaderProgram( const char * vertexFileName, const char * fragmentFileName )
{
	load( vertexFileName, fragmentFileName );
}

ShaderProgram::~ShaderProgram()
{
	//dtor
}

void ShaderProgram::load(  const char * vertexFileName, const char * fragmentFileName )
{
	std::string vertexCode   = readFile ( vertexFileName );
	GLuint vertexShaderId   = compileShader( GL_VERTEX_SHADER, vertexCode );

	std::string fragmentCode = readFile ( fragmentFileName );
	GLuint fragmentShaderId = compileShader( GL_FRAGMENT_SHADER, fragmentCode );


	if ( vertexShaderId && fragmentShaderId ) { // all is ok

		id = linkProgram( vertexShaderId, fragmentShaderId ); // remember program by id

		glDeleteShader( vertexShaderId );	// free shader resources
		glDeleteShader( fragmentShaderId );	// free shader resources
	} else {
		id = 0; // no program on error
	}
}


GLuint ShaderProgram::getUniformLocation( const char * aName )
{
	return glGetUniformLocation( id, aName );
}
GLuint ShaderProgram::getAttribLocation(  const char * aName  )
{
	return glGetAttribLocation( id, aName );
}
/**
 * make this shaderprogram the active one
 */
void ShaderProgram::use()
{
	glUseProgram( id ); // make this the active shaderprogram
}

void ShaderProgram::draw( unsigned int count )
{
	glDrawElements( GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

// private members

// read the shader code into string
std::string ShaderProgram::readFile( const char * fileName )
{
	// Read the Vertex Shader code from the file
	std::string code;
	std::ifstream file ( fileName, std::ios::in);
	if(file.is_open()){
		std::cout << "Reading shader " << fileName << std::endl;
		std::string line = "";
		while(getline(file, line)) { 	// read per line
			code += "\n" + line;		// add to string
		}
		file.close(); // close on finish
	} else {
		std::cout << "Error reading shader " << fileName << std::endl;
		code = "";
	}
	return code;
}

// compile the code, and detect errors.
GLuint ShaderProgram::compileShader( GLenum type, std::string & shaderCode)
{
	std::cout << "Compiling shader " << std::endl;

	// Compile Vertex Shader
	const char * codePointer = shaderCode.c_str();
	GLuint shaderId = glCreateShader( type  ); // get shader id
	glShaderSource( shaderId, 1, &codePointer , NULL );
	glCompileShader( shaderId );

	// Check compiler result
	GLint result = GL_FALSE;
	glGetShaderiv( shaderId, GL_COMPILE_STATUS, &result);

	if ( result ) {
		std::cout << "Shader compiled ok" << std::endl;
		return shaderId;
	} else { // get error message
		int count;
		glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &count);
		//std::vector<char> errorMessage( count+1 );
		char errorMessage[ count+1 ];
		glGetShaderInfoLog( shaderId, count, NULL, errorMessage);
		std::cout << errorMessage << std::endl;
		return 0; // no shader id
	}
}

// link the two shaders and return the program id
GLuint ShaderProgram::linkProgram ( GLuint vertexShaderId, GLuint fragmentShaderId )
{
	// Link the program
	GLuint programId = glCreateProgram();
	glAttachShader( programId, vertexShaderId);
	glAttachShader( programId, fragmentShaderId);
	glLinkProgram( programId);

	// Check the program
	GLint result = GL_FALSE;
	glGetProgramiv( programId, GL_LINK_STATUS, &result );
	if ( result ) {
		std::cout << "program linked ok" << std::endl;
		return programId;
	} else { // error, show message
		int count;
		glGetProgramiv( programId, GL_INFO_LOG_LENGTH, &count );
		//std::vector<char> ProgramErrorMessage( max(count, int(1)) );
		char errorMessage[ count+1 ];
		glGetProgramInfoLog( programId, count, NULL, errorMessage );
		std::cout << errorMessage << std::endl;
		return 0;
	}
}


