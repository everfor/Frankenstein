#version 330

in vec2 tex0;
in vec3 worldPos0;
in mat3 tbn;

uniform vec3 ambientIntensity;
uniform vec3 eyePos;
uniform sampler2D diffuse;
uniform sampler2D dispMap;
uniform float dispScale;
uniform float dispBias;

out vec4 gl_FragColor;

vec2 getDispTexCoord(vec3 eyePos, sampler2D dispMap, float dispScale, float dispBias)
{
	vec3 directionToEye = normalize(eyePos - worldPos0);
	return tex0.xy + (directionToEye * tbn).xy * (texture2D(dispMap, tex0.xy).r * dispScale + dispBias);
}

void main()
{
	vec2 tex = getDispTexCoord(eyePos, dispMap, dispScale, dispBias);
    gl_FragColor = texture(diffuse, tex) * vec4(ambientIntensity, 1.0);
}
