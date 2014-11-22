#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform PointLight pointLight;

void main()
{
	gl_FragColor = texture(diffuse, tex0.xy) * calculatePointLight(pointLight, getNormal(normalMap), worldPos0);
}