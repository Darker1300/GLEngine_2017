#version 410

in vec2 vUV;

uniform vec3 ambientMat = vec3(1,1,1);
uniform sampler2D diffuseMap;

out vec4 fragColour;

void main()
{
	vec4 tex = texture(diffuseMap, vUV);
	// Simple transparency
	if(tex.a != 1.00) discard;

	fragColour = tex * vec4(ambientMat, 1.0f);
}
