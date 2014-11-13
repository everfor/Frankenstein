#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;

out vec2 tex0;

uniform mat4 transform;

void main()
{
	tex0 = textCoord;
	gl_Position = transform * vec4(position, 1.0);
}
