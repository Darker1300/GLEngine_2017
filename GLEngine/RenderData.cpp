#include "DEBUG_NEW_LEAK_DETECT.h"

#include "DEBUG_WINDOWS_ERR_MSG.h"
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
	if (m_VAO != -1 || m_VBO != -1 || m_IBO != -1) {
		LOG_ERROR("Buffers have already been created.")
	}

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
	if (m_VAO == -1) {
		LOG_ERROR("You are binding an invalid buffer.")
	}
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
