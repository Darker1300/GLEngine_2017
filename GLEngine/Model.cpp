#include "Model.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm\glm.hpp>

Model::Model()
{
}


Model::~Model()
{
}

void Model::GeneratePlane(unsigned int rows, unsigned int cols)
{
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r) {
		for (unsigned int c = 0; c < cols; ++c) {
			aoVertices[r * cols + c].position = glm::vec4((float)c, 0, (float)r, 1); // create some arbitrary colour based off something 
																					 // that might not be related to tiling a texture
			glm::vec3 colour = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r * cols + c].colour = glm::vec4(colour, 1);
		}
	}

	// Gen
	glGenBuffers(1, &m_VertexBufferObject);
	glGenBuffers(1, &m_IndexBufferObject);

	glGenVertexArrays(1, &m_VertexArrayObject);

	// Bind
	glBindVertexArray(m_VertexArrayObject);

	// defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			// triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			// triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}
	delete[] aoVertices;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
