#include "DEGUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Model.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "ShaderProgram.h"

Model::Model()
	: m_VertexArrayObj(-1), m_VertexBufferObj(-1), m_IndexBufferObj(-1),
	m_vertexCount(), m_indexCount(), m_geometryType(GL_TRIANGLES)
{
}


Model::~Model()
{
}

void Model::GeneratePlane(unsigned int rows, unsigned int cols)
{
	// ------ Create CPU Model Data ------
	// Create Verts
	unsigned int vertexCount = rows * cols;
	Vertex* aoVertices = new Vertex[vertexCount];
	for (unsigned int r = 0; r < rows; ++r) {
		for (unsigned int c = 0; c < cols; ++c) {
			aoVertices[r * cols + c].position = glm::vec4((float)c, 0, (float)r, 1); // create some arbitrary colour based off something 
																					 // that might not be related to tiling a texture
			glm::vec3 colour = glm::vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			aoVertices[r * cols + c].colour = glm::vec4(colour, 1);
		}
	}

	// Create Indices. Defining index count based off quad count (2 triangles per quad)
	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	unsigned int* auiIndices = new unsigned int[indexCount];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			// Triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			// Triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	// Set additional Model info
	m_vertexCount = vertexCount;
	m_indexCount = indexCount;
	m_geometryType = GL_TRIANGLES;

	// ------ Move to GPU ------

	// Gen Vert, Index, VA
	glGenBuffers(1, &m_VertexBufferObj);
	glGenBuffers(1, &m_IndexBufferObj);
	glGenVertexArrays(1, &m_VertexArrayObj);

	// Bind VA
	glBindVertexArray(m_VertexArrayObj);

	// Bind Index
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);


	// Bind Vert
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);


	// Enable Arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	// Set Attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	// Bind Array Buf
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Cleanup cpu data
	delete[] aoVertices;
	delete[] auiIndices;
}

void Model::DrawModel(ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	DrawModel(this, _shader, _projectionViewMatrix);
}

void Model::DrawModel(Model * _model, ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	// Use Shader
	glUseProgram(_shader->m_programID);
	// Get projectionViewGlobalMatrix uniform location
	unsigned int projectionViewUniformLocation = glGetUniformLocation(_shader->m_programID, "projectionViewWorldMatrix");
	// Test ^ if failed
	if (projectionViewUniformLocation == -1) {
		DEBUG::ERROR_MSG("glGetUniformLocation(projectionViewWorldMatrix) failed.");
	}
	// Apply matrix CPU-->GPU
	glUniformMatrix4fv(projectionViewUniformLocation, 1, false, glm::value_ptr(*_projectionViewMatrix));
	
	// Bind Vertex and Index buffers
	glBindVertexArray(_model->m_VertexArrayObj);
	// Draw
	glDrawElements(_model->m_geometryType, _model->m_indexCount, GL_UNSIGNED_INT, 0);
}
