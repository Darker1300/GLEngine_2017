#include "DEGUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Mesh.h"

#include "ShaderProgram.h"

#include <gl_core_4_4.h>
#include <glm\ext.hpp>

Mesh::Mesh()
	: m_VertexArrayObj(-1), m_VertexBufferObj(-1), m_IndexBufferObj(-1),
	m_vertexCount(), m_indexCount(), m_geometryType(GL_TRIANGLES)
{
}


Mesh::~Mesh()
{
}

void Mesh::DrawMesh(ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	DrawMesh(this, _shader, _projectionViewMatrix);
}

void Mesh::DrawMesh(Mesh * _model, ShaderProgram * _shader, glm::mat4 * _projectionViewMatrix)
{
	// Use Shader
	glUseProgram(_shader->m_programID);

	// ----- Uniforms -----
	// Get projectionViewGlobalMatrix uniform location
	unsigned int projectionViewUniformLocation = glGetUniformLocation(_shader->m_programID, "projectionViewWorldMatrix");
	// Test ^ if failed
	if (projectionViewUniformLocation != 0) {
		LOG_ERROR("glGetUniformLocation( projectionViewWorldMatrix ) failed.")
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
