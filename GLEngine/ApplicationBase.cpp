#include "ApplicationBase.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm/ext.hpp>

#if defined(_WINDOWS_) && defined(_DEBUG)
#include <Windows.h>
#endif

ApplicationBase::ApplicationBase()
{
	m_windowWidth = 1280;
	m_windowHeight = 720;

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Game Engine", nullptr, nullptr);

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		ERROR_MSG("LOAD FAILED.");
		return;
	}


	m_GLMajor = ogl_GetMajorVersion();
	m_GLMinor = ogl_GetMinorVersion();

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH);

	m_view = glm::lookAt(
		glm::vec3(10, 10, 10),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	m_projection = glm::perspective(
		glm::pi<float>() * 0.25f,
		(float)m_windowWidth / (float)m_windowHeight,
		0.1f, 1000.0f);

	glfwDestroyWindow(m_window);
	glfwTerminate();
	return;
}


ApplicationBase::~ApplicationBase()
{
}

void ApplicationBase::Run()
{
	if (Startup() == 0)
	{
		while (glfwWindowShouldClose(m_window) == false)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (Update() != 0) { ERROR_MSG("Application Update Failed."); }
			if (Draw() != 0) { ERROR_MSG("Application Draw Failed."); }

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		if (Shutdown() != 0) {
			ERROR_MSG("Application Shutdown Failed.");
		}
	}
	else { ERROR_MSG("Application Startup Failed."); }
}

int ApplicationBase::Startup()
{
	return 0;
}

int ApplicationBase::Update()
{
	return 0;
}

int ApplicationBase::Draw()
{
	return 0;
}

int ApplicationBase::Shutdown()
{
	return 0;
}

inline void ApplicationBase::ERROR_MSG(const char * _msg) {
#if defined(_WINDOWS_) && defined(_DEBUG)
	MessageBox(NULL, _msg, "Error", MB_ICONERROR);
#endif
}
