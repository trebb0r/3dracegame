#include "glm.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

Camera::Camera( std::string aName, glm::vec3 aPosition )
:	GameObject(aName, aPosition )
{
	glm::vec3 eye = aPosition;
	glm::vec3 at ( 0.0f, 0.0f, 0.0f );
	glm::vec3 up ( 0.0f, 1.0f, 0.0f );
	transform = glm::inverse( glm::lookAt( eye, at, up ) );
	projection = glm::perspective(  60.0f, 4.0f/3.0f, 0.1f, 25.0f  );
}

Camera::~Camera()
{
	//dtor
}

void Camera::draw( Renderer * renderer, glm::mat4 parentTransform )
{
	//std::cout << "Camera sets View " << std::endl << transform << std::endl;
	renderer->clear( glm::vec4( 0.1f, 0.1f, 0.1f, 1.0f ) ); // clear screen with color

	renderer->setProjection( projection ); // model = cam to worldspace so inverse for world->camspace
	renderer->setView( glm::inverse( transform ) ); // model = cam to worldspace so inverse for world->camspace
}
