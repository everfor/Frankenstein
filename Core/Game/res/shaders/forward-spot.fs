#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform SpotLight spotLight;

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
	gl_FragColor = texture(diffuse, tex) * calcualteSpotLight(spotLight, getNormal(normalMap, tex), worldPos0);
}