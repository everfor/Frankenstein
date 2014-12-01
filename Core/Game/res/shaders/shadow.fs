#version 330
out vec4 gl_FragColor;

void main()
{
	gl_FragColor = vec4(gl_FragCoord.z, gl_FragCoord.z * gl_FragCoord.z, 0.0, 0.0);
	// gl_FragColor = vec4(gl_FragCoord.z);
}
