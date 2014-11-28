#version 330
#include "common.vsh"
uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
}
