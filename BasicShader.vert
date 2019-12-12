#version 330 core

uniform mat3 mvp;

in vec2 position;
in vec3 color;

out vec3 frag_color;


void main()
{
	vec3 pos = mvp * vec3(position, 1.0);
	gl_Position = vec4(pos, 1.0);
	frag_color = color;
}