#pragma once
#include <glm\glm.hpp>

namespace gl {

	const struct SHADER_BASE
	{
		const static char* vertexSource;
		const static char* fragmentSource;
		struct Vertex {
			glm::vec4 position;
		};
	};

	const struct SHADER_STD : SHADER_BASE
	{
		// struct Vertex : SHADER_BASE::Vertex {
		// 	glm::vec4 colour;
		// };
	};

};
