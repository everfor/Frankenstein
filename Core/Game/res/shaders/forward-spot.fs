#version 330
#include "lighting.glh"

in vec2 tex0;
in vec3 normal0;
in vec3 worldPos0;

out vec4 gl_FragColor;

uniform SpotLight spotLight;

void main()
{
	gl_FragColor = texture(diffuse, tex0.xy) * calcualteSpotLight(spotLight, normalize(normal0), worldPos0);
}