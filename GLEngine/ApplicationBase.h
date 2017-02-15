#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	void Run();
	virtual int Startup();
	virtual int Update();
	virtual int Draw();
	virtual int Shutdown();

	inline void ERROR_MSG(const char* _msg);

	int m_windowWidth;
	int m_windowHeight;
	int m_GLMajor;
	int m_GLMinor;
	GLFWwindow* m_window;
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

