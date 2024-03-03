#version 330 core

// Vertex position, coming from vertex buffer
layout (location = 0) in vec3 p;

// Ball info, coming from CPU
uniform vec2 center;

// Transform matrices
uniform mat4 model;
uniform mat4 projection;

// Point to send for fragment shader
varying vec4 pos;

void main()
{
	// Transform vertex based on ball radius and aspect ratio
	vec4 vert = projection * model * vec4(p, 1.0f);

	// Update vertex position
	gl_Position = vert;

	// Send unchanged vertex position to fragment shader so it remains in (-1, 1) range
	pos = vec4(p, 1.0f);
}
