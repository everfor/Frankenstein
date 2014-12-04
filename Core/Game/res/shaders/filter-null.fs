#version 330

in vec2 tex0;

uniform sampler2D filterMap;

out vec4 gl_FragColor;

void main()
{
    gl_FragColor = texture(filterMap, tex0);
}
