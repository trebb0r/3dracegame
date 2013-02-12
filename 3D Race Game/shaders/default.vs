#version 130 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	projection;	// set for all vertices
uniform	mat4 	view;			// set for all vertices
uniform	mat4 	model;		// set for all vertices
uniform	vec3 	light;		// set for all vertices

in vec3 vertex; 					// attribute-input per vertex from vertices
in vec3 normal;						// attribute-input per normal from normals
in vec2 uv;

out vec2 texCoord; // uv forwarded to fs
out float intensity;

void main( void ){
	gl_Position = projection * view * model * vec4( vertex, 1.f );
	vec4 worldPosition = model * vec4( vertex, 1.0f );
	vec4 worldNormal = model * vec4( normal, 0.0f ); // note the 0.0f
	vec4 lightDir = normalize( vec4( light, 1.0f ) - worldPosition );
	intensity = dot( worldNormal, lightDir );
	intensity = clamp( intensity, 0.0f, 1.0f );

	texCoord = uv; // gives interpolated uv in fs
}
