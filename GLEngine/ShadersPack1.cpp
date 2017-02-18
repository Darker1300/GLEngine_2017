#include "ShadersPack.h"


namespace SSP {
	const extern char* vertexSource =
		"	\
		#version 410 \n\n	\
		layout(location=0) in vec4 position;	\
		layout(location=1) in vec4 colour;	\
		out vec4 vColour;	\
		uniform mat4 projectionViewWorldMatrix;	\
		void main()	\
		{	\
			vColour = colour;	\
			gl_Position = projectionViewWorldMatrix * position;	\
		}	\
			\
		";

	const extern char* fragmentSource =
		"	\
		#version 410 \n\n	\
		in vec4 vColour;	\
		out vec4 fragColour;	\
		void main()	\
		{	\
			fragColour = vColour;	\
		}	\
			\
		";
}
