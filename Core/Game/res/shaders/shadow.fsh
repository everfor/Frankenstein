uniform sampler2D shadowMap;
uniform float shadowMinVariance;
uniform float lightBleedThreshold;

float linearStep(float low, float high, float value)
{
	return clamp((value - low) / (high - low), low, high);
}

float sampleVarianceShadow(sampler2D shadowMap, vec3 shadowMapCoords, float compare)
{
	vec2 moment = texture(shadowMap, shadowMapCoords.xy).xy;

	float p = step(compare, moment.x);
	float variance = max(moment.y - moment.x * moment.x, shadowMinVariance);

	float d = compare - moment.x;
	float pmax = linearStep(lightBleedThreshold, 1.0, variance / (variance + d * d));

	return min(max(p, pmax), 1.0);
	// return step(compare, texture(shadowMap, shadowMapCoords.xy).x);
}

float calculateShadowAmount(sampler2D shadowMap, vec4 shadowMapCoords)
{
	vec3 shadowCoords = (shadowMapCoords.xyz / shadowMapCoords.w) * vec3(0.5) + vec3(0.5);

	return sampleVarianceShadow(shadowMap, shadowCoords, shadowCoords.z);
}