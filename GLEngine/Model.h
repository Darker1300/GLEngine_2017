#pragma once
#include <glm\glm.hpp>

class Model
{
public:
	Model();
	~Model();
	// our vertex and index buffers
	unsigned int m_VertexArrayObject;
	unsigned int m_VertexBufferObject;
	unsigned int m_IndexBufferObject;

	struct Vertex {
		glm::vec4 position;
		glm::vec4 colour;
	};

	void GeneratePlane(unsigned int rows, unsigned int cols);
};

