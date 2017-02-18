#pragma once
#include <glm\glm.hpp>

class ShaderProgram;

class Mesh
{
public:
	Mesh();
	~Mesh();
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

	void GenerateBuffers();
	void DrawMesh(ShaderProgram* _shader, glm::mat4* _projectionViewMatrix);
	static void DrawMesh(Mesh* _model, ShaderProgram* _shader, glm::mat4* _projectionViewMatrix);
protected:

};
