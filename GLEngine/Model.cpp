#include "DEGUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Model.h"

#include "ShaderProgram.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <vector>
#include <cmath>

Model::Model()
	: m_VertexArrayObj(-1), m_VertexBufferObj(-1), m_IndexBufferObj(-1),
	m_vertexCount(), m_indexCount(), m_geometryType(GL_TRIANGLES)
{
}


Model::~Model()
{
}

void Model::DrawModel(ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	DrawModel(this, _shader, _projectionViewMatrix);
}

void Model::DrawModel(Model * _model, ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	// Use Shader
	glUseProgram(_shader->m_programID);

	// ----- Uniforms -----
	// Get projectionViewGlobalMatrix uniform location
	unsigned int projectionViewUniformLocation = glGetUniformLocation(_shader->m_programID, "projectionViewWorldMatrix");
	// Test ^ if failed
	if (projectionViewUniformLocation != 0) {
		DEBUG::ERROR_MSG("glGetUniformLocation( projectionViewWorldMatrix ) failed.");
	}
	// Apply matrix uniform CPU-->GPU
	glUniformMatrix4fv(projectionViewUniformLocation, 1, false, glm::value_ptr(*_projectionViewMatrix));
	// --------------------

	// Bind Vertex and Index buffers
	glBindVertexArray(_model->m_VertexArrayObj);
	// Draw
	glDrawElements(_model->m_geometryType, _model->m_indexCount, GL_UNSIGNED_INT, 0);
	// Unbind Vertex and Index buffers
	glBindVertexArray(0);

}

Model * Primatives::Plane(const unsigned int _rows, const unsigned int _cols)
{
	// ------ Create CPU Model Data ------
	// Create Verts
	unsigned int vertexCount = _rows * _cols;
	Model::Vertex* aoVertices = new Model::Vertex[vertexCount];
	for (unsigned int r = 0; r < _rows; ++r) {
		for (unsigned int c = 0; c < _cols; ++c) {
			aoVertices[r * _cols + c].position = glm::vec4((float)c, 0, (float)r, 1); // create some arbitrary colour based off something 
																					 // that might not be related to tiling a texture
			glm::vec3 colour = glm::vec3(sinf((c / (float)(_cols - 1)) * (r / (float)(_rows - 1))));
			aoVertices[r * _cols + c].colour = glm::vec4(colour, 1);
		}
	}

	// Create Indices. Defining index count based off quad count (2 triangles per quad)
	unsigned int indexCount = (_rows - 1) * (_cols - 1) * 6;
	unsigned int* auiIndices = new unsigned int[indexCount];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (_rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (_cols - 1); ++c)
		{
			// Triangle 1
			auiIndices[index++] = r * _cols + c;
			auiIndices[index++] = (r + 1) * _cols + c;
			auiIndices[index++] = (r + 1) * _cols + (c + 1);
			// Triangle 2
			auiIndices[index++] = r * _cols + c;
			auiIndices[index++] = (r + 1) * _cols + (c + 1);
			auiIndices[index++] = r * _cols + (c + 1);
		}
	}

	Model* plane = new Model();

	// Set additional Model info
	plane->m_vertexCount = vertexCount;
	plane->m_indexCount = indexCount;
	plane->m_geometryType = GL_TRIANGLES;

	// ------ Move to GPU ------

	// Vertex
	glGenBuffers(1, &plane->m_VertexBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, plane->m_VertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Model::Vertex), aoVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index
	glGenBuffers(1, &plane->m_IndexBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane->m_IndexBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// VA
	glGenVertexArrays(1, &plane->m_VertexArrayObj);
	glBindVertexArray(plane->m_VertexArrayObj);
	// Bind VBO & IBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, plane->m_VertexBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane->m_IndexBufferObj);

	// ----- Set Attribute details -----
	// position:
	// Enable Arrays
	glEnableVertexAttribArray(0);
	// Set Attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Model::Vertex), (void*)offsetof(Model::Vertex, Model::Vertex::position));

	// colour:
	// Enable Arrays
	glEnableVertexAttribArray(1);
	// Set Attribute pointers
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(unsigned int), (void*)offsetof(Model::Vertex, Model::Vertex::colour));

	// ---------------------------------

	// Bind Array Buf
	glBindVertexArray(0);

	// Cleanup cpu data
	delete[] aoVertices;
	delete[] auiIndices;

	return plane;
}

Model * Primatives::Sphere(const float _radius, const unsigned int _rings, const unsigned int _sectors)
{
	std::vector<Model::Vertex> vertices;
	//std::vector<GLfloat> normals;
	//std::vector<GLfloat> texcoords;
	std::vector<unsigned int> indices;

	float const R = 1.f / (float)(_rings - 1);
	float const S = 1.f / (float)(_sectors - 1);
	float const pi = glm::pi<float>();
	float const piHalf = glm::half_pi<float>();
	int r, s;

	vertices.resize(_rings * _sectors * 3);
	//	normals.resize(_rings * _sectors * 3);
	//	texcoords.resize(_rings * _sectors * 2);
	std::vector<Model::Vertex>::iterator v = vertices.begin();
	//	std::vector<GLfloat>::iterator n = normals.begin();
	//	std::vector<GLfloat>::iterator t = texcoords.begin();
	for (r = 0; r < (int)_rings; r++) for (s = 0; s < (int)_sectors; s++) {
		float const y = sin(-piHalf + pi * r * R);
		float const x = cos(2 * pi * s * S) * sin(pi * r * R);
		float const z = sin(2 * pi * s * S) * sin(pi * r * R);

		// Texture Co-ord
		//	*t++ = s*S;
		//	*t++ = r*R;

		// Position
		glm::vec4 pos = glm::vec4(x * _radius, y * _radius, z * _radius, 1);
		v->position = pos;

		// Colour
		glm::vec4 colour = glm::vec4(sinf(x), sinf(x * 10), sinf((x * 10) * y), 1);
		v->colour = colour;

		// Normal
		//	*n++ = x;
		//	*n++ = y;
		//	*n++ = z;
		v++;
	}

	indices.resize(_rings * _sectors * 4);
	std::vector<unsigned int>::iterator i = indices.begin();
	for (r = 0; r < (int)_rings - 1; r++) for (s = 0; s < (int)_sectors - 1; s++) {
		*i++ = r * _sectors + s;
		*i++ = r * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + s;
	}

	Model* sphere = new Model();

	// Set additional Model info
	sphere->m_vertexCount = vertices.size();
	sphere->m_indexCount = indices.size();
	sphere->m_geometryType = GL_QUADS;

	// ------ Move to GPU ------
		// Vertex
	glGenBuffers(1, &sphere->m_VertexBufferObj);
	glBindBuffer(GL_ARRAY_BUFFER, sphere->m_VertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Model::Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Index
	glGenBuffers(1, &sphere->m_IndexBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere->m_IndexBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// VA
	glGenVertexArrays(1, &sphere->m_VertexArrayObj);
	glBindVertexArray(sphere->m_VertexArrayObj);
	// Bind VBO & IBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, sphere->m_VertexBufferObj);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere->m_IndexBufferObj);

	// ----- Set Attribute details -----
	// position:
	// Enable Arrays
	glEnableVertexAttribArray(0);
	// Set Attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Model::Vertex), (void*)offsetof(Model::Vertex, Model::Vertex::position));

	// colour:
	// Enable Arrays
	glEnableVertexAttribArray(1);
	// Set Attribute pointers
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Model::Vertex), (void*)offsetof(Model::Vertex, Model::Vertex::colour));
	// ---------------------------------

	// Bind Array Buf
	glBindVertexArray(0);

	return sphere;
}
