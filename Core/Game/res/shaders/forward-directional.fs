#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform DirectionalLight directionalLight;

void main()
{
	gl_FragColor = texture(diffuse, tex0.xy) * calculateDirectionalLight(directionalLight, getNormal(normalMap), worldPos0);
}