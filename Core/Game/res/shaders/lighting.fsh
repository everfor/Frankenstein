in vec2 tex0;
in vec3 worldPos0;
in mat3 tbn;
in vec4 shadowMapCoords0;

out vec4 gl_FragColor;

vec3 getNormal(sampler2D normalMap, vec2 tex)
{
	return normalize(tbn * (texture2D(normalMap, tex).xyz * 2.0 - vec3(1, 1, 1)));
}

vec2 getDispTexCoord(vec3 eyePos, sampler2D dispMap, float dispScale, float dispBias)
{
	vec3 directionToEye = normalize(eyePos - worldPos0);
	return tex0.xy + (directionToEye * tbn).xy * (texture2D(dispMap, tex0.xy).r * dispScale + dispBias);
}