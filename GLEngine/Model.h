#pragma once
#include <glm\glm.hpp>

class ShaderProgram;

class Model
{
public:
	Model();
	~Model();
	// our vertex and index buffers
	unsigned int m_VertexArrayObj;
	unsigned int m_VertexBufferObj;
	unsigned int m_IndexBufferObj;

	unsigned int m_vertexCount;
	unsigned int m_indexCount;
	// GType eg GL_TRIANGLES = 4
	unsigned int m_geometryType;

	struct Vertex {
		glm::vec4 position;
		glm::vec4 colour;
	};

	void DrawModel(ShaderProgram* _shader, glm::mat4* _projectionViewMatrix);
	static void DrawModel(Model* _model, ShaderProgram* _shader, glm::mat4* _projectionViewMatrix);
};

namespace Primatives
{
	Model* Plane(const unsigned int _rows, const unsigned int _cols);
	Model* Sphere(const float _radius, const unsigned int _rings, const unsigned int _sectors);
}
