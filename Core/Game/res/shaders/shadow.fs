#version 330
out vec4 gl_FragDepth;

void main()
{
	gl_FragDepth = vec4(gl_FragCoord.z);
}
