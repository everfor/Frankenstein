#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 normal;

out vec2 tex0;
out vec3 normal0;

uniform mat4 transform;
uniform mat4 projection;

void main()
{
	tex0 = textCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
	gl_Position = projection * vec4(position, 1.0);
}
