#version 330 core

// Vertex position
layout (location = 0) in vec3 p;

// Point for frag shader
varying vec2 pos;

void main()
{
	gl_Position = vec4(p, 1.0);
	pos = vec2(gl_Position.x, gl_Position.y);
}
