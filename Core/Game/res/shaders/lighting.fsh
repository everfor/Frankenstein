in vec2 tex0;
in vec2 normalcoord0;
in vec3 worldPos0;
in mat3 tbn;

out vec4 gl_FragColor;

vec3 getNormal(sampler2D normalMap)
{
	return normalize(tbn * (texture2D(normalMap, normalcoord0.xy).xyz * 2.0 - 1.0));
}