#version 330

in vec2 tex0;

uniform vec3 color;
uniform sampler2D sampler;

out vec4 gl_FragColor;

void main()
{
	gl_FragColor = texture(sampler, tex0.xy) * vec4(color, 1.0);
}
