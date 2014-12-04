#version 330

/*
* 7 x 1 Gauss Blur Filter
*/

in vec2 tex0;

uniform vec3 blurScale;
uniform sampler2D filterMap;

out vec4 gl_FragColor;

void main()
{
	vec4 color = vec4(0.0);

	color += texture(filterMap, tex0 + (vec3(-3.0) * blurScale).xy) * (1.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(-2.0) * blurScale).xy) * (6.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(-1.0) * blurScale).xy) * (15.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(0.0) * blurScale).xy) * (20.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(1.0) * blurScale).xy) * (15.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(2.0) * blurScale).xy) * (6.0 / 64.0);
	color += texture(filterMap, tex0 + (vec3(3.0) * blurScale).xy) * (1.0 / 64.0);

    gl_FragColor = color;
}
