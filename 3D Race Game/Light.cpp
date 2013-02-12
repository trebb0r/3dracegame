#include "Light.hpp"

#include "Renderer.hpp"

Light::Light( std::string aName, glm::vec3 aPosition )
:	GameObject( aName, aPosition )
{
}

Light::~Light()
{
	//dtor
}

void Light::draw( Renderer * aRenderer, glm::mat4 parentTransform )
{
	aRenderer->setLight( getLocation() );
}
