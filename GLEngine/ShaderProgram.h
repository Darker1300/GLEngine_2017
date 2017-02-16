#pragma once

class VertexShader
{
public:
	VertexShader(const char* _source);
	~VertexShader();
	unsigned int m_shaderID;
};

class FragmentShader
{
public:
	FragmentShader(const char* _source);
	~FragmentShader();
	unsigned int m_shaderID;
};

class ShaderProgram
{
public:
	ShaderProgram(VertexShader& _vShader, FragmentShader& _fShader);
	~ShaderProgram();

	unsigned int m_programID;
};
