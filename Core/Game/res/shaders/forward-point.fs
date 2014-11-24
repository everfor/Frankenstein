#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform PointLight pointLight;

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
	gl_FragColor = texture(diffuse, tex) * calculatePointLight(pointLight, getNormal(normalMap, tex), worldPos0);
}