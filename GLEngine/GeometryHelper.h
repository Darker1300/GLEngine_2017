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
		// x, y, z, w
		glm::vec4 position;
		// u, v
		glm::vec2 uv;
		// nx, ny, nz, nw
		glm::vec4 normal;
		// tx, ty, tz, tw
		glm::vec4 tangent;
		// btx, bty, btz, btw
		glm::vec4 bitangent;
	};

	RenderData* CreatePlane(const unsigned int _rows, const unsigned int _cols, const float _width, const float _height, const glm::vec4& _colour);
	RenderData* CreateQuad(const float _width, const float _height, glm::vec3 facingDirection, const glm::vec4& _colour);

	std::vector<RenderData*> LoadOBJFromDisk(const std::string& _path);
	void CalculateTangents(std::vector<OBJVertex>& vertices);


};

