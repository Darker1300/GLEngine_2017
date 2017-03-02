#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 colour;
layout(location=2) in vec2 uv;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out vec4 vColour;
out vec2 vUV;

void main()
{
	vColour = colour;
	vUV = uv;
	mat4 PVM = projectionViewMatrix * modelMatrix;
	gl_Position = PVM * position;
}
