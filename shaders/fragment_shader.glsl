#version 330 core

#define ALPHA_OFFSET 0.005f

// Ball radius, coming from CPU
uniform float radius;

// Frag pos, coming from vertex shader
varying vec4 pos;

void main()
{
	// Normalize coordinate range from (-1, 1) to (0, 1) for UV
	vec4 uv = pos * 0.5f + 0.5f;

	// Check for distance
	float dist = distance(uv.xy, vec2(0.5f));
	if (dist > 0.5f) {
		discard;
	}

	// Smooth border alpha, based on ball radius to avoid blurring
	// balls that are very small
	float alpha = smoothstep(0.5f, 0.5f - ALPHA_OFFSET * 0.5f / max(radius, 0.05f), dist);

	// Final color
	gl_FragColor = vec4(uv.xy, 0.0f, alpha);
}
