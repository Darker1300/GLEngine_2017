#pragma once
#include <string>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragPath);
	~Shader();

	Shader(const Shader& _other) = delete;
	Shader(Shader&& _other);

	Shader& operator=(const Shader& _other) = delete;

	unsigned int GetProgramID() const { return m_programID; }

private:
	void			MakeShaderProgram(const std::string& _vertexPath, const std::string& _fragPath);
	unsigned int	MakeShader(unsigned int _type, const std::string& _path);
	void			TestCompilation();
	std::string		LoadText(const std::string& _path);

	unsigned int	m_programID;
};
