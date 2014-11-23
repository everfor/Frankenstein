#version 330
#include "common.vsh"

out vec2 tex0;

uniform mat4 MVP;

void main()
{
    tex0 = textCoord;
    gl_Position = MVP * vec4(position, 1.0);
}
