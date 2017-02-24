#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class RenderData;

namespace GeometryHelper
{
	struct SimpleVertex {
			glm::vec4 position;
			glm::vec4 colour;
	};

	static RenderData* CreateGrid(const unsigned int _rows, const unsigned int _cols, const float _width, const float _height, const glm::vec4 _colour);
	static RenderData* CreateQuad(const float _width, const float _height, glm::vec3 facingDirection, const glm::vec4 _colour);
};

