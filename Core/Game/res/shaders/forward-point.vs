#version 330
#include "common.vsh"
#include "lighting.vsh"

void main()
{
	tex0 = textCoord;
	worldPos0 = (model * vec4(position, 1.0)).xyz;
	tbn = mat3(normalize((model * vec4(tangent, 0.0)).xyz), normalize((model * vec4(bitangent, 0.0)).xyz), normalize((model * vec4(normal, 0.0)).xyz));
	gl_Position = MVP * vec4(position, 1.0);
}