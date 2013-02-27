#include "Mesh.hpp"

#include <map>
#include <cstring>
#include <fstream>

#include "Renderer.hpp"

Mesh::Mesh()
:	indicesBuffer(0), verticesBuffer(0), normalsBuffer(0), uvsBuffer(0)
{
	//ctor
}

Mesh::~Mesh()
{
	//dtor
}

unsigned int Mesh::size() {
	return indices.size();
}

void Mesh::draw( Renderer * aRenderer )
{
	aRenderer->draw( size(), indicesBuffer, verticesBuffer, normalsBuffer, uvsBuffer );
}


// static functions

// reads the obj data into a new mesh: note here is C++ combined with c style
// the result is an indexed mesh for use with glDrawElements
// expects a obj file with v/vt/vn
Mesh * Mesh::load( const char * fileName )
{
	assert( fileName != NULL );
	assert( strlen( fileName ) > 0 );

	Mesh * mesh = new Mesh();

	std::ifstream file ( fileName, std::ios::in );

	if( file.is_open() ){ // file opened succesfully so it exists
		std::vector<glm::vec3> vertices; // for the indexed data
		std::vector<glm::vec3> normals; // for the indexed data
		std::vector<glm::vec2> uvs; // for the indexed data

		std::map< PackedIndex, unsigned int> keys; // used to convert to indexed arrays

		std::string line; // to store each line in
		while( getline( file, line ) ) { // as long as there are lines to be read
			char cmd[10]; // c-type string to store cmd
			cmd[0] = 0;
			sscanf ( line.c_str(), "%10s", cmd ); // get the first string in the line of max 5 chars (c-style)
			if ( strcmp ( cmd, "v" ) == 0 ) { // line with vertex
				glm::vec3 vertex;
				sscanf( line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z );
				vertices.push_back( vertex );
			} else if ( strcmp ( cmd, "vn" ) == 0 ) { // line with normal
				glm::vec3 normal;
				sscanf( line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z );
				normals.push_back( normal );
			} else if ( strcmp ( cmd, "vt" ) == 0 ) { // line with uv
				glm::vec2 uv;
				sscanf( line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y );
				uvs.push_back( uv );
			} else if ( strcmp ( cmd, "f" ) == 0 ) { // line with face
				glm::ivec3 vertexIndex; // to store the indices
				glm::ivec3 normalIndex;
				glm::ivec3 uvIndex;
				int count = sscanf( line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				//std::cout << line << std::endl;
				if ( count == 10 ) { // there should be 10 args to be read
					for ( int i = 0; i < 3; ++i ) { // make verticesArray out of indexed array
						PackedIndex key (vertexIndex[i], normalIndex[i], uvIndex[i]);
						std::map< PackedIndex, unsigned int>::iterator found = keys.find( key );
						if ( found == keys.end() ) { // key is new
							unsigned int index = keys.size();
							//std::cout << "new i " <<  index << " " << mesh->indices.size() << " : " << vertices[vertexIndex[i]-1] << std::endl;
							keys[ key ] = index;
							mesh->indices.push_back( index );
							mesh->vertices.push_back( vertices[ vertexIndex[i]-1 ] );
							mesh->normals.push_back( normals[ normalIndex[i]-1 ] );
							mesh->uvs.push_back( uvs[ uvIndex[i]-1 ] );
						} else { // key already present
							unsigned int index = found->second;
							//std::cout << "old i " <<  index << " " << mesh->indices.size() << " : " << vertices[vertexIndex[i]-1] << std::endl;
							mesh->indices.push_back( index );
						}
					}
				} else { // something is wrong
					std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
					delete mesh; // free the mem from created body
					return NULL; // no body read
				}
			}
		}
		file.close();
		std::cout << "Done loading " << fileName;
		mesh->buffer();
		std::cout << " and buffering " << std::endl;
		return mesh;
	} else { // file could not be opened;
		std::cout << "Could not read " << fileName << std::endl;
		delete mesh;
		return NULL;
	}
}

void Mesh::buffer()
{
	// create vertices buffer
	if ( ! indicesBuffer ) { // if not buffered yet
		glGenBuffers( 1, &indicesBuffer  );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indicesBuffer  );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		glGenBuffers(1, &verticesBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, verticesBuffer ); // working on vertices buffer
			glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0][0], GL_STATIC_DRAW );
		glGenBuffers(1, &normalsBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, normalsBuffer ); // working on normals buffer
			glBufferData( GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0][0], GL_STATIC_DRAW );
		glGenBuffers(1, &uvsBuffer );
			glBindBuffer( GL_ARRAY_BUFFER, uvsBuffer ); // working on uvs buffer
			glBufferData( GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0][0], GL_STATIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // important for 2d sfml
	}
}

void Mesh::unBuffer()
{
	if ( indicesBuffer ) {
		glDeleteBuffers( 1, & indicesBuffer );
		glDeleteBuffers( 1, & verticesBuffer );
		glDeleteBuffers( 1, & normalsBuffer );
		glDeleteBuffers( 1, & uvsBuffer );
		indicesBuffer = 0;
		verticesBuffer = 0;
		normalsBuffer = 0;
		uvsBuffer= 0;
		std::cout << "Unbuffering" << std::endl;
	}
}
