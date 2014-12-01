#version 330
#include "lighting.glh"
#include "lighting.fsh"

uniform DirectionalLight directionalLight;
uniform sampler2D shadowMap;

float sampleVarianceShadow(sampler2D shadowMap, vec3 shadowMapCoords, float compare)
{
	vec2 moment = texture(shadowMap, shadowMapCoords.xy).xy;

	float p = step(compare, moment.x);
	float variance = max(moment.y - moment.x * moment.x, 0.0002);

	float d = compare - moment.x;
	float pmax = variance / (variance + d * d);

	return min(max(p, pmax), 1.0);
	// return step(compare, texture(shadowMap, shadowMapCoords.xy).x);
}

float calculateShadowAmount(sampler2D shadowMap, vec4 shadowMapCoords)
{
	vec3 shadowCoords = (shadowMapCoords.xyz / shadowMapCoords.w) * vec3(0.5) + vec3(0.5);

	return sampleVarianceShadow(shadowMap, shadowCoords, shadowCoords.z);
}

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
	gl_FragColor = texture(diffuse, tex) * calculateDirectionalLight(directionalLight, getNormal(normalMap, tex), worldPos0) * calculateShadowAmount(shadowMap, shadowMapCoords0);
}