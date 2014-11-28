#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform DirectionalLight directionalLight;
uniform sampler2D shadowMap;

float calculateShadowAmount(sampler2D shadowMap, vec4 shadowMapCoords)
{
	vec3 shadowCoords = (shadowMapCoords.xyz / shadowMapCoords.w) * vec3(0.5) + vec3(0.5);

	return step(shadowCoords.z - 0.00001, texture2D(shadowMap, shadowCoords.xy).r);
}

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
	gl_FragColor = texture(diffuse, tex) * calculateDirectionalLight(directionalLight, getNormal(normalMap, tex), worldPos0) * calculateShadowAmount(shadowMap, shadowMapCoords0);
}