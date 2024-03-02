#version 330 core

#define ALPHA_OFFSET 0.005

// Ball radius, coming from CPU
uniform float radius;

// Frag pos, coming from vertex shader
varying vec2 pos;

void main()
{
	// Normalize coordinate range from (-1, 1) to (0, 1) for UV
	vec2 uv = pos * 0.5 + 0.5;

	// Check for distance
	float dist = distance(uv, vec2(0.5));
	if (dist > 0.5) {
		discard;
	}

	// Smooth border alpha, based on ball radius to avoid blurring
	// balls that are very small
	float alpha = smoothstep(0.5, 0.5 - ALPHA_OFFSET * 0.5 / max(radius, 0.05), dist);

	// Final color
	gl_FragColor = vec4(uv, 0.0, alpha);
}
