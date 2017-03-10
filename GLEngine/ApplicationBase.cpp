#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "ApplicationBase.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>


ApplicationBase* GLE::APP = nullptr;

ApplicationBase::ApplicationBase(std::string _title, int _width, int _height)
{
	m_windowTitle = _title;
	m_windowWidth = _width;
	m_windowHeight = _height;
}

ApplicationBase::~ApplicationBase()
{
}

void ApplicationBase::Run()
{
	static double second = 1.0f;
	m_targetFPS = 60.0;
	m_fixedDTInterval = second * m_targetFPS;

	double lastTime = glfwGetTime(), timer = lastTime;
	double deltaTime = 0, fixedDeltaTime = 0, nowTime = 0;
	int currentFPS = 0, fixedUpdates = 0;

	// PreInitialise Event
	if (PreInitialise()) { LOG_ERROR("ApplicationBase.PreInitialise Failed.") }
	// Initialise Event
	if (Initialise()) { LOG_ERROR("ApplicationBase.Initialise Failed.") }
	// Start Event
	if (Start()) { LOG_ERROR("ApplicationBase.Start Failed.") }

	// While window is alives
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
			if (FixedUpdate(m_fixedDTInterval)) { LOG_ERROR("ApplicationBase.FixedUpdate Failed.") }

			// Measure timing
			fixedUpdates++;
			fixedDeltaTime -= second;
		}
		// Update Event
		if (Update(deltaTime)) { LOG_ERROR("ApplicationBase.Update Failed.") }
		// LateUpdate Event
		if (LateUpdate(deltaTime)) { LOG_ERROR("ApplicationBase.LateUpdate Failed.") }

		// Draw Event, at maximum possible frames
		if (Draw()) { LOG_ERROR("ApplicationBase.Draw Failed.") }

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
	if (Shutdown()) { LOG_ERROR("ApplicationBase.Shutdown Failed.") }
	// Finalise Event
	if (Finalise()) { LOG_ERROR("ApplicationBase.Finalise Failed.") }
}

int ApplicationBase::PreInitialise()
{
	GLE::APP = this;
	return 0;
}

int ApplicationBase::Initialise()
{
	CreateOGLWindow();
	return 0;
}

int ApplicationBase::Finalise()
{
	DestroyOGLWindow();
	GLE::APP = nullptr;
	return 0;
}

bool ApplicationBase::InitialiseOGLFunctions()
{
	// Check LoadFunctions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		LOG_ERROR("OGL LoadFunctions Failed.")
			return false;
	}
	return true;
}

bool ApplicationBase::CreateOGLWindow()
{
	// Init GLFW
	if (glfwInit() == false)
	{
		LOG_ERROR("GLFW Initialisation Failed")
			return false;
	}
	// Create Window
	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowTitle.c_str(), nullptr, nullptr);
	if (m_window == false) return false;

	// Create Context
	glfwMakeContextCurrent(m_window);

	// Load Functions
	InitialiseOGLFunctions();

	// Set Defaults
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetBackgroundColor(0.0f, 0.0f, 0.0f);

	return true;
}

void ApplicationBase::DestroyOGLWindow()
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

GLFWwindow * ApplicationBase::GetWindow()
{
	return m_window;
}

void ApplicationBase::GetOGLVersion(int & _outMajor, int & _outMinor)
{
	_outMajor = ogl_GetMajorVersion();
	_outMinor = ogl_GetMinorVersion();
}

int ApplicationBase::GetFPS()
{
	return m_FPS;
}

int ApplicationBase::GetFUPS()
{
	return m_FUPS;
}

void ApplicationBase::SetBackgroundColor(float _r, float _g, float _b, float _a)
{
	glClearColor(_r, _g, _b, _a);
}
