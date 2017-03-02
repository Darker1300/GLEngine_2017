#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

class RenderData;

namespace GeometryHelper
{
	struct SimpleVertex {
		glm::vec4 position;
		glm::vec4 colour;
		glm::vec2 uv;
	};

	struct OBJVertex {
		// x, y, z
		glm::vec4 position;
		// nx, ny, nz
		glm::vec3 normal;
		// u, v
		glm::vec2 uv;
	};

	RenderData* CreatePlane(const unsigned int _rows, const unsigned int _cols, const float _width, const float _height, const glm::vec4& _colour);
	RenderData* CreateQuad(const float _width, const float _height, glm::vec3 facingDirection, const glm::vec4& _colour);

	std::vector<RenderData*> LoadOBJFromDisk(const std::string& _path);
};

