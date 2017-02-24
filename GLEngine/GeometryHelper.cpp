#include "DEBUG_NEW_LEAK_DETECT.h"

#include "GeometryHelper.h"

#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include "RenderData.h"

namespace GeometryHelper {
	RenderData * CreateGrid(const unsigned int _rows, const unsigned int _cols, const float _width, const float _height, const glm::vec4& _colour)
	{
		// Vertices
		unsigned int verticesSize = _rows * _cols;
		SimpleVertex* vertices = new SimpleVertex[verticesSize];
		float rowSpacing = _width / (_rows - 1);
		float colSpacing = _height / (_cols - 1);

		// Vertices Generation
		for (unsigned int r = 0; r < _rows; r++)
		{
			for (unsigned int c = 0; c < _cols; c++)
			{
				SimpleVertex& vert = vertices[r * _cols + c];
				// Pos
				vert.position = glm::vec4(
					-(_width / 2) + (colSpacing * c), 0,
					-(_height / 2) + (rowSpacing * r), 1);
				// Colour
				vert.colour = _colour;
			}
		}
		// Indices
		unsigned int indicesSize = (_rows - 1) * (_cols - 1) * 6;
		unsigned int* indices = new unsigned int[indicesSize];

		// Indices Generation
		unsigned int index = 0;
		for (unsigned int r = 0; r < (_rows - 1); ++r)
		{
			for (unsigned int c = 0; c < (_cols - 1); ++c)
			{
				// Triangle 1
				indices[index++] = r * _cols + c;
				indices[index++] = (r + 1) * _cols + c;
				indices[index++] = (r + 1) * _cols + (c + 1);
				// Triangle 2
				indices[index++] = r * _cols + c;
				indices[index++] = (r + 1) * _cols + (c + 1);
				indices[index++] = r * _cols + (c + 1);
			}
		}

		// Store on GPU
		RenderData* renderData = new RenderData();
		renderData->GenerateBuffers();

		// Bind VAO (includes VBO & IBO)
		renderData->Bind();
		// Send Vertices
		glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(SimpleVertex), vertices, GL_STATIC_DRAW);
		// Send Indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		// Let OpenGL know where to find the data in the vertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(SimpleVertex),
			(char*)offsetof(SimpleVertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(SimpleVertex),
			(char*)offsetof(SimpleVertex, colour));

		// Unbind VAO (includes VBO & IBO)
		renderData->Unbind();

		// Configure RenderData
		renderData->SetIndicesSize(indicesSize);
		renderData->SetPrimitiveType(GL_TRIANGLES);

		// Delete cpu-side data
		delete[] vertices;
		delete[] indices;

		return renderData;
	}

	RenderData * CreateQuad(const float _width, const float _height, glm::vec3 facingDirection, const glm::vec4& _colour)
	{
		return nullptr;
	}
}
