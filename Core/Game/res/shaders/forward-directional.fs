#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform DirectionalLight directionalLight;

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
	gl_FragColor = texture(diffuse, tex) * calculateDirectionalLight(directionalLight, getNormal(normalMap, tex), worldPos0);
}