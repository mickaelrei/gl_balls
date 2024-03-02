#version 330 core

// Vertex position, coming from vertex buffer
layout (location = 0) in vec3 p;

// Ball info, coming from CPU
uniform vec2 center;
uniform float radius;

// Window aspect ratio (TODO: Change this to a mat2 to transform vertex)
uniform float aspectRatio;

// Point to send for fragment shader
varying vec2 pos;

void main()
{
	// Transform vertex based on ball radius and aspect ratio
	vec2 vert = p.xy * radius;
	vert.x /= aspectRatio;

	// Update vertex position
	gl_Position = vec4(vert + center, 0.0, 1.0);

	// Send unchanged vertex position to fragment shader so it remains in (-1, 1) range
	pos = p.xy;
}
