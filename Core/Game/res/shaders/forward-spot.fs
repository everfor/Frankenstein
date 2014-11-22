#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform SpotLight spotLight;

void main()
{
	gl_FragColor = texture(diffuse, tex0.xy) * calcualteSpotLight(spotLight, getNormal(normalMap), worldPos0);
}