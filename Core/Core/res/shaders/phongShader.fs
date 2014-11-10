#version 330

in vec2 tex0;

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

out vec4 gl_FragColor;

void main()
{
	vec4 textureColor = texture(sampler, tex0.xy);
	vec4 color = vec4(baseColor, 1.0);

	// Lighting
	vec4 totalLight = vec4(ambientLight, 1.0);

	if (textureColor != vec4(0, 0, 0, 0))
	{
		color *= textureColor;
	}

	gl_FragColor = color * totalLight;
}
