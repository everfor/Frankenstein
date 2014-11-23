in vec2 tex0;
in vec3 worldPos0;
in mat3 tbn;

out vec4 gl_FragColor;

vec3 getNormal(sampler2D normalMap)
{
	return normalize(tbn * (texture2D(normalMap, tex0.xy).xyz * 2.0 - vec3(1, 1, 1)));
}