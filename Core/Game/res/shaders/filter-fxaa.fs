#version 330

in vec2 tex0;

uniform sampler2D filterMap;

out vec4 gl_FragColor;

void main()
{
	vec2 texSize = textureSize(filterMap, 0);
	vec2 texelSize = vec2(1.0 / texSize.x, 1.0 / texSize.y);
	
	// MAGIC
	vec3 luminosity = vec3(0.299, 0.587, 0.114);
	float luminosityTopLeft = dot(texture(filterMap, tex0.xy + vec2(-1.0, -1.0) * texelSize).xyz, luminosity);
	float luminosityTopRight = dot(texture(filterMap, tex0.xy + vec2(1.0, -1.0) * texelSize).xyz, luminosity);
	float luminosityBottomLeft = dot(texture(filterMap, tex0.xy + vec2(-1.0, 1.0) * texelSize).xyz, luminosity);
	float luminosityBottomRight = dot(texture(filterMap, tex0.xy + vec2(1.0, 1.0) * texelSize).xyz, luminosity);
	float luminosityCenter = dot(texture(filterMap, tex0.xy).xyz, luminosity);

	// Blur direction
	vec2 dir;
	float reduction = max(1.0/64.0, (luminosityTopLeft + luminosityTopRight + luminosityBottomLeft + luminosityBottomRight) * (1.0/4.0 * 0.25));
	dir.x = -((luminosityTopLeft + luminosityTopRight) - (luminosityBottomLeft + luminosityBottomRight));
	dir.y = ((luminosityTopLeft + luminosityBottomRight) - (luminosityTopRight + luminosityBottomRight));

	dir = dir * (1.0 / (min(abs(dir.x), abs(dir.y)) + reduction));
	dir = clamp(dir, vec2(-8.0, -8.0), vec2(8.0, 8.0)) * texelSize;

	// Calculate results
	vec3 closerBlur = (1.0 / 2.0)  * (
			texture(filterMap, tex0.xy + dir * vec2(1.0/3.0 - 0.5)).xyz + 
			texture(filterMap, tex0.xy + dir * vec2(2.0/3.0 - 0.5)).xyz
		);

	vec3 furtherBlur = closerBlur * (1.0 / 2.0) + (1.0 / 4.0)  * (
			texture(filterMap, tex0.xy + dir * vec2(0.0/3.0 - 0.5)).xyz + 
			texture(filterMap, tex0.xy + dir * vec2(3.0/3.0 - 0.5)).xyz
		);

	float luminosityMin = min(luminosityCenter, min(min(luminosityTopLeft, luminosityTopRight), min(luminosityBottomLeft, luminosityBottomRight)));
	float luminosityMax = max(luminosityCenter, max(max(luminosityTopLeft, luminosityTopRight), max(luminosityBottomLeft, luminosityBottomRight)));
	float furtherBlurResult = dot(luminosity, furtherBlur);

	if (furtherBlurResult < luminosityMin || furtherBlurResult > luminosityMax)
	{
		gl_FragColor = vec4(closerBlur, 1.0);
	}
	else
	{
		gl_FragColor = vec4(furtherBlur, 1.0);
	}
}
