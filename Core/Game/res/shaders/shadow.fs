#version 330
out vec4 gl_FragColor;

void main()
{
	float depth = gl_FragCoord.z;

	float dx = dFdx(depth);
	float dy = dFdy(depth);
	float second_moment = depth * depth * 0.25 * (dx * dx) * (dy * dy);

	gl_FragColor = vec4(1.0 - depth, 1.0 - second_moment, 0.0, 0.0);
	// gl_FragColor = vec4(gl_FragCoord.z);
}
