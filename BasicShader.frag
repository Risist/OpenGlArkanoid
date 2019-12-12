#version 330 core	

in vec3 frag_color;
out vec4 outColor;

void main()
{
	outColor = vec4( frag_color, 1);
}