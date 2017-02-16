#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#if defined(_WINDOWS_) && defined(_DEBUG)
#include <Windows.h>
#endif

#include "ApplicationBase.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <iostream>

ApplicationBase::ApplicationBase()
{
}

ApplicationBase::~ApplicationBase()
{
}

void ApplicationBase::Run(int _windowWidth, int _windowHeight)
{
	m_windowWidth = _windowWidth;
	m_windowHeight = _windowHeight;

	static double second = 1.0;
	m_targetFPS = 60.0;
	m_fixedDTInterval = second / m_targetFPS;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, fixedDeltaTime = 0, nowTime = 0;
	int currentFPS = 0, fixedUpdates = 0;

	// PreInitialise Event
	if (PreInitialise() != 0) { ERROR_MSG("ApplicationBase.PreInitialise Failed."); }
	// Initialise Event
	if (Initialise() != 0) { ERROR_MSG("ApplicationBase.Initialise Failed."); }
	// Start Event
	if (Start() != 0) { ERROR_MSG("ApplicationBase.Start Failed."); }

	// While window is alive
	while (glfwWindowShouldClose(m_window) == false)
	{
		// Clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Measure time
		nowTime = glfwGetTime();
		deltaTime = nowTime - lastTime;
		fixedDeltaTime += deltaTime / m_fixedDTInterval;
		lastTime = nowTime;

		// Only FixedUpdate at fixed frames / s
		while (fixedDeltaTime >= second) {
			// FixedUpdate Event
			if (FixedUpdate(m_fixedDTInterval) != 0) { ERROR_MSG("ApplicationBase.FixedUpdate Failed."); }
			
			// Measure timing
			fixedUpdates++;
			fixedDeltaTime -= second;
		}
		// Update Event
		if (Update(deltaTime) != 0) { ERROR_MSG("ApplicationBase.Update Failed."); }
		// LateUpdate Event
		if (LateUpdate(deltaTime) != 0) { ERROR_MSG("ApplicationBase.LateUpdate Failed."); }

		// Draw Event, at maximum possible frames
		if (Draw() != 0) { ERROR_MSG("ApplicationBase.Draw Failed."); }

		// Double Buffer
		glfwSwapBuffers(m_window);

		// Gather Window Inputs
		glfwPollEvents();

		// FPS this second
		currentFPS++;

		// Reset after one second
		if (glfwGetTime() - timer > second) {
			timer += second;
			m_FPS = currentFPS;
			m_FUPS = fixedUpdates;
			fixedUpdates = 0, currentFPS = 0;
		}
	}
	// Shutdown Event
	if (Shutdown() != 0) { ERROR_MSG("ApplicationBase.Shutdown Failed."); }
	// Finalise Event
	if (Finalise() != 0) { ERROR_MSG("ApplicationBase.Finalise Failed."); }
}

int ApplicationBase::Initialise()
{
	InitialiseWindow();
	return 0;
}

int ApplicationBase::Finalise()
{
	FinaliseWindow();
	return 0;
}

inline void ApplicationBase::ERROR_MSG(const char * _msg) {
#if defined(_WINDOWS_) && defined(_DEBUG)
	MessageBox(NULL, _msg, "ERROR", MB_ICONERROR);
#endif
}

void ApplicationBase::InitialiseWindow()
{
	if (glfwInit() == false)
	{
		ERROR_MSG("GL Initialisation Failed");
		return;
	}

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

	return;
}

void ApplicationBase::FinaliseWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
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

int ApplicationBase::GetFPS()
{
	return m_FPS;
}

int ApplicationBase::GetFUPS()
{
	return m_FUPS;
}
