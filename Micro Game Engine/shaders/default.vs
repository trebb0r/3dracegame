#version 150 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	projection;	// set for all vertices
uniform	mat4 	view;			// set for all vertices
uniform	mat4 	model;		// set for all vertices
uniform	vec3 	light;		// set for all vertices
uniform	float 	time;		// set for all vertices

in vec3 vertex; 					// attribute-input per vertex from vertices
in vec3 normal;						// attribute-input per normal from normals
in vec2 uv;

out vec2 texCoord; // uv forwarded to fs
out float intensity;

void main( void ){
	//gl_Position = projection * view * model * vec4( vertex, 1.f );

	//some funny stuff, manipulating vertex (optically)
	vec3 manipulatedVertex = vertex;
	manipulatedVertex.x += manipulatedVertex.y * manipulatedVertex.y * sin( time ) *0.25;
	gl_Position = projection * view * model * vec4( manipulatedVertex, 1.0f );

	// calc light direction
	vec4 worldPosition = model * vec4( vertex, 1.0f ); // position of vertex in world
	vec4 worldNormal = model * vec4( normal, 0.0f ); // direction of normal in world, note the 0.0f
	vec4 lightDir = normalize( vec4( light, 1.0f ) - worldPosition ); // direction of light, normalized
	intensity = dot( worldNormal, lightDir ); // get overlap normal and lightdir
	intensity = clamp( intensity, 0.0f, 1.0f ); // set boundaries

	texCoord = uv; // gives interpolated uv in fs
}
