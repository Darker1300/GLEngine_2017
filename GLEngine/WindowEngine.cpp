#include "WindowEngine.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "CoreDefines.h"

#include <gl_core_4_4.h>
#include <glfw\glfw3.h>


WindowEngine::WindowEngine()
	: m_window()
	, m_title()
	, m_width()
	, m_height()
	, m_sizeChanged(true)
{
}

WindowEngine::~WindowEngine()
{
}

void WindowEngine::Core_EndFrame()
{
	// Gather Window Inputs
	glfwPollEvents();
	// Refresh Screen size
	if (m_sizeChanged)
		glViewport(0, 0, m_width, m_height);
}

bool WindowEngine::Core_ShouldWindowClose()
{
	return glfwWindowShouldClose(m_window);
}

void WindowEngine::Initialize()
{
	if (ENGINE::WINDOW != nullptr) LOG_ERROR("Attempted to Initialize WindowEngine multiple times.");

	ENGINE::WINDOW = new WindowEngine();

	ENGINE::WINDOW->SetSize(800, 600);
	ENGINE::WINDOW->CreateOGLWindow();
	glfwSetWindowSizeCallback(ENGINE::WINDOW->m_window, WindowSizeCallback);
}

void WindowEngine::Finalize()
{
	if (ENGINE::WINDOW == nullptr) LOG_ERROR("Failed to Finalize WindowEngine.");

	ENGINE::WINDOW->DestroyOGLWindow();

	delete ENGINE::WINDOW;
}

bool WindowEngine::InitialiseOGLFunctions()
{
	// Check LoadFunctions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		LOG_ERROR("OGL LoadFunctions Failed.")
			return false;
	}
	return true;
}

bool WindowEngine::CreateOGLWindow()
{
	// Init GLFW
	if (glfwInit() == false)
	{
		LOG_ERROR("GLFW Initialisation Failed")
			return false;
	}
	// Create Window
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
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

	return true;
}

void WindowEngine::DestroyOGLWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void WindowEngine::WindowSizeCallback(GLFWwindow * _window, int _width, int _height)
{
	ENGINE::WINDOW->m_width = _width;
	ENGINE::WINDOW->m_height = _height;
	ENGINE::WINDOW->m_sizeChanged = true;
}

GLFWwindow * WindowEngine::Window() const
{
	return m_window;
}

std::string WindowEngine::Title() const
{
	return m_title;
}

unsigned int WindowEngine::Width() const
{
	return m_width;
}

unsigned int WindowEngine::Height() const
{
	return m_height;
}

float WindowEngine::AspectRatio() const
{
	return (float)m_width / (float)m_height;
}

void WindowEngine::SetTitle(const char * _title)
{
	glfwSetWindowTitle(m_window, _title);
}

void WindowEngine::SetSize(unsigned int _width, unsigned int _height)
{
	m_width = _width;
	m_height = _height;
	glfwSetWindowSize(m_window, m_width, m_height);
	m_sizeChanged = true;
}
