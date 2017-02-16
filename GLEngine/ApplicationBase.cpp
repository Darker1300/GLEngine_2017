#include "ApplicationBase.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <iostream>

#if defined(_WINDOWS_) && defined(_DEBUG)
#include <Windows.h>
#endif

ApplicationBase::ApplicationBase(int _windowWidth, int _windowHeight)
{
	if (glfwInit() == false)
	{
		ERROR_MSG("GL Inititalation Failed");
		return;
	}

	m_windowWidth = _windowWidth;
	m_windowHeight = _windowHeight;

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

}

ApplicationBase::~ApplicationBase()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void ApplicationBase::Run()
{
	static double second = 1.0;
	static double targetFPS = 60.0;
	static double intervalFPS = second / targetFPS;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, fixedDeltaTime = 0, nowTime = 0;
	int currentFPS = 0, fixedUpdates = 0;

	// Start Event
	if (Start() != 0) { ERROR_MSG("ApplicationBase.Startup Failed."); }
	// While window is alive
	while (glfwWindowShouldClose(m_window) == false)
	{
		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Measure time
		nowTime = glfwGetTime();
		deltaTime = nowTime - lastTime;
		fixedDeltaTime += deltaTime / intervalFPS;
		lastTime = nowTime;

		// Only update at 60 frames / s
		while (fixedDeltaTime >= second) {
			// FixedUpdate Event
			if (FixedUpdate(intervalFPS) != 0) { ERROR_MSG("ApplicationBase.FixedUpdate Failed."); }
			fixedUpdates++;
			fixedDeltaTime -= second;
		}
		// Update Event
		if (Update(deltaTime) != 0) {
			ERROR_MSG("ApplicationBase.Update Failed.");
		}
		// LateUpdate Event
		if (LateUpdate(deltaTime) != 0) { ERROR_MSG("ApplicationBase.LateUpdate Failed."); }

		// Draw Event, at maximum possible frames
		if (Draw() != 0) { ERROR_MSG("ApplicationBase.Draw Failed."); }
		glfwSwapBuffers(m_window);

		// Gather Window Inputs
		glfwPollEvents();

		// FPS this second
		currentFPS++;

		// Reset after one second
		if (glfwGetTime() - timer > second) {
			timer += second;
			std::cout << "FPS: " << currentFPS << " Updates:" << fixedUpdates << std::endl;
			fixedUpdates = 0, currentFPS = 0;
		}
	}
	if (Shutdown() != 0) { ERROR_MSG("ApplicationBase.Shutdown Failed."); }
}

inline void ApplicationBase::ERROR_MSG(const char * _msg) {
#if defined(_WINDOWS_) && defined(_DEBUG)
	MessageBox(NULL, _msg, "ERROR", MB_ICONERROR);
#endif
}

int ApplicationBase::GetWindowWidth()
{
	return m_windowWidth;
}

int ApplicationBase::GetWindowHeight()
{
	return m_windowHeight;
}

void ApplicationBase::GetOGLVersion(int & _outMajor, int & _outMinor)
{
	_outMajor = m_GLMajor;
	_outMinor = m_GLMinor;
}
