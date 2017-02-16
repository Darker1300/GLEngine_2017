#include "ShaderProgram.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <iostream>

VertexShader::VertexShader(const char * _source)
{
	m_shaderID = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(m_shaderID, 1, &_source, 0);
	glCompileShader(m_shaderID);

}

VertexShader::~VertexShader()
{
}

FragmentShader::FragmentShader(const char * _source)
{
	m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_shaderID, 1, &_source, 0);
	glCompileShader(m_shaderID);
}

FragmentShader::~FragmentShader()
{
}

ShaderProgram::ShaderProgram(VertexShader & _vShader, FragmentShader & _fShader)
{
	m_programID = glCreateProgram();
	glAttachShader(m_programID, _vShader.m_shaderID);
	glAttachShader(m_programID, _fShader.m_shaderID);
	glLinkProgram(m_programID);

	int success = GL_FALSE;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		// DEBUG
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glDeleteShader(_vShader.m_shaderID);
	glDeleteShader(_fShader.m_shaderID);
}

ShaderProgram::~ShaderProgram()
{
}
