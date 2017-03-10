#version 410

in vec4 vColour;
in vec2 vUV;

uniform sampler2D diffuse;

out vec4 gl_FragColor;

void main()
{
	vec4 tex = texture(diffuse, vUV);
	// Simple transparency
	if(tex.a < 0.1) discard;

	gl_FragColor = tex * vColour;
}
