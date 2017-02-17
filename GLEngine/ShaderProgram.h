#pragma once

class IShaderBase
{
public:
	friend class ShaderProgram;

	IShaderBase(unsigned int _shaderType, const char* _source);
	virtual ~IShaderBase();

	unsigned int m_shaderID;

protected:
	void AttachLinkShaders(ShaderProgram* _container);
	void DeleteComponent();
};

struct VertexShader : public IShaderBase {
	VertexShader(const char* _source);
	~VertexShader();
};

struct FragmentShader : public IShaderBase {
	FragmentShader(const char* _source);
	~FragmentShader();
};

class ShaderProgram
{
public:
	ShaderProgram(IShaderBase** _shaders, int _count);
	ShaderProgram(VertexShader* _vertex, FragmentShader* _fragment);
	~ShaderProgram();

	void SetupShaderProgram();

	unsigned int m_programID;
	IShaderBase** m_shaders;
	int m_shadersCount;

protected:
	void CreateProgramID();
	void AttachLinkShaders();
	void TestCompilation();
	void DeleteShaders();
};
