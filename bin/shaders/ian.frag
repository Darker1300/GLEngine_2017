#version 410

in vec4 vColour;
in vec2 vUV;

uniform sampler2D diffuse;

out vec4 fragColour;

void main()
{
	fragColour =  texture(diffuse,vUV);// * vColour;
}
