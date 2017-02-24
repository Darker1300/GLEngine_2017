#include "DEBUG_NEW_LEAK_DETECT.h"
#include "RenderData.h"

#include <gl_core_4_4.h>
#include <assert.h>

#define DEFAULT_PRIMITIVE_TYPE GL_TRIANGLES

RenderData::RenderData()
	: m_VAO(-1)
	, m_VBO(-1)
	, m_IBO(-1)
	, m_primitiveType(DEFAULT_PRIMITIVE_TYPE)
	, m_indicesSize(0)
{
}

RenderData::RenderData(RenderData && _other)
{
	m_VAO = _other.m_VAO;
	m_VBO = _other.m_VBO;
	m_IBO = _other.m_IBO;
	m_primitiveType = _other.m_primitiveType;
	m_indicesSize = _other.m_indicesSize;

	_other.m_VAO = -1;
	_other.m_VBO = -1;
	_other.m_IBO = -1;
	_other.m_indicesSize = 0;
	_other.m_primitiveType = DEFAULT_PRIMITIVE_TYPE;
}

void RenderData::GenerateBuffers()
{
	assert(m_VAO == -1 && "Buffers have already been created.");
	assert(m_VBO == -1);
	assert(m_IBO == -1);

	// Gen
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	// Bind
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	// Unbind
	glBindVertexArray(0);
}

void RenderData::Render() const
{
	Bind();
	glDrawElements(m_primitiveType, m_indicesSize, GL_UNSIGNED_INT, 0);
	Unbind();
}

void RenderData::Bind() const
{
	assert(m_VAO == -1 && "You arae binding an invalid buffer.");
	glBindVertexArray(m_VAO);
}

void RenderData::Unbind() const
{
	glBindVertexArray(0);
}

RenderData::~RenderData()
{
	DestroyBuffers();
}

void RenderData::DestroyBuffers()
{
	if (m_VAO != -1)
		glDeleteBuffers(1, &m_VAO);
	if (m_VBO != -1)
		glDeleteBuffers(1, &m_VBO);
	if (m_IBO != -1)
		glDeleteBuffers(1, &m_IBO);
}

// Fill
// glBufferData(GL_ARRAY_BUFFER, _vertexSize * sizeof(vertexType), _vertexFirst, GL_STATIC_DRAW);
// // Index
// glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexSize * sizeof(unsigned int), _indexFirst, GL_STATIC_DRAW);
// // Bind VB & IB to VA
// glBindBuffer(GL_ARRAY_BUFFER, arr->m_B_Vertex_ID);
// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arr->m_B_Index_ID);
