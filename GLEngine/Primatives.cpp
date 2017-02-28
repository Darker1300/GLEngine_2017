#include "Primatives.h"
#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Mesh.h"

#include <gl_core_4_4.h>
#include <GlFW\glfw3.h>
#include <glm\ext.hpp>
#include <vector>
#include <cmath>
#include "VertexArray.h"
#include "ShaderCollection.h"

Mesh * Primatives::Plane(const unsigned int _rows, const unsigned int _cols)
{
#define STD_Vert gl::SHADER_TEX::Vertex

	// ------ Create CPU Mesh Data ------
	// Create Verts
	unsigned int verticesSize = _rows * _cols;
	STD_Vert* vertices = new STD_Vert[verticesSize];

#pragma region  Generate Mesh

	for (unsigned int r = 0; r < _rows; ++r)
	{
		for (unsigned int c = 0; c < _cols; ++c)
		{
			STD_Vert& vert = vertices[r * _cols + c];
			// Position
			vert.m_positionLocal = glm::vec4((float)c, 0, (float)r, 1);
			// TexCoord
			vert.texCoord = glm::vec2(r * (1.0f / _rows), c * (1.0f / _cols));
			// Colour
			glm::vec3 colour = glm::vec3(sinf((c / (float)(_cols - 1)) * (r / (float)(_rows - 1))));
			vert.colour = glm::vec4(colour, 1);
		}
	}

	// Create Indices. Defining index count based off quad count (2 triangles per quad)
	unsigned int indicesSize = (_rows - 1) * (_cols - 1) * 6;
	unsigned int* indices = new unsigned int[indicesSize];

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

#pragma endregion Generate Mesh

	Mesh* plane = new Mesh();

	// Set additional Mesh info
	plane->m_vertexCount = verticesSize;
	plane->m_indexCount = indicesSize;
	plane->m_geometryType = GL_TRIANGLES;


	// ------ Copy to GPU ------
	plane->m_vertexArray = gl::VertexArray::Create<STD_Vert>(vertices, verticesSize, indices, indicesSize);

	// ----- Set Attribute details -----

	// Bind Array
	plane->m_vertexArray->bind();

	// m_positionLocal:
	// Enable Arrays
	glEnableVertexAttribArray(0);
	// Set Attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::m_positionLocal));

	// colour:
	// Enable Arrays
	glEnableVertexAttribArray(1);
	// Set Attribute pointers
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::colour));

	// texCoord:
	// Enable Arrays
	glEnableVertexAttribArray(2);
	// Set Attribute pointers
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::texCoord));

	// Unbind Array
	plane->m_vertexArray->bind(false);
	// ---------------------------------

	// Cleanup cpu data
	delete[] vertices;
	delete[] indices;

	return plane;
}

Mesh * Primatives::Sphere(const float _radius, const unsigned int _rings, const unsigned int _sectors)
{
#define STD_Vert gl::SHADER_TEX::Vertex

	std::vector<STD_Vert> vertices;
	std::vector<unsigned int> indices;

#pragma region Generate Mesh

	float const R = 1.f / (float)(_rings - 1);
	float const S = 1.f / (float)(_sectors - 1);
	float const pi = glm::pi<float>();
	float const piHalf = glm::half_pi<float>();
	int r, s;

	vertices.resize(_rings * _sectors * 3);
	std::vector<STD_Vert>::iterator v = vertices.begin();
	for (r = 0; r < (int)_rings; r++) for (s = 0; s < (int)_sectors; s++) {
		float const y = sin(-piHalf + pi * r * R);
		float const x = cos(2 * pi * s * S) * sin(pi * r * R);
		float const z = sin(2 * pi * s * S) * sin(pi * r * R);

		// Position
		glm::vec4 pos = glm::vec4(x * _radius, y * _radius, z * _radius, 1);
		v->m_positionLocal = pos;

		// Colour
		glm::vec4 colour = glm::vec4(cosf(y), cosf(y * 10), cosf((y * 10) * x), 1);
		v->colour = colour;

		// Texture Co-ord
		v->texCoord = glm::vec2(s*S, r*R);

		// Normal
		//v->normal = glm::vec3(x,y,z);
		v++;
	}

	// Indices
	indices.resize(_rings * _sectors * 4);
	std::vector<unsigned int>::iterator i = indices.begin();
	for (r = 0; r < (int)_rings - 1; r++) for (s = 0; s < (int)_sectors - 1; s++) {
		*i++ = r * _sectors + s;
		*i++ = r * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + (s + 1);
		*i++ = (r + 1) * _sectors + s;
	}

#pragma endregion Generate Mesh

	Mesh* sphere = new Mesh();

	// Set additional Mesh info
	sphere->m_vertexCount = vertices.size();
	sphere->m_indexCount = indices.size();
	sphere->m_geometryType = GL_QUADS;

	// ------ Copy to GPU ------
	sphere->m_vertexArray = gl::VertexArray::Create<STD_Vert>(&vertices[0], vertices.size(), &indices[0], indices.size());

	// ----- Set Attribute details -----
	// Bind Array
	sphere->m_vertexArray->bind();

	// m_positionLocal:
	//		Enable Arrays
	glEnableVertexAttribArray(0);
	//		Set Attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::m_positionLocal));

	// colour:
	//		Enable Arrays
	glEnableVertexAttribArray(1);
	//		Set Attribute pointers
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::colour));

	// texCoord:
	//		Enable Arrays
	glEnableVertexAttribArray(2);
	//		Set Attribute pointers
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(STD_Vert), (void*)offsetof(STD_Vert, STD_Vert::texCoord));

	// Unbind Array
	sphere->m_vertexArray->bind(false);
	// ---------------------------------

	return sphere;
}
