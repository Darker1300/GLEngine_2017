
#include "WindowEngine.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "CoreDefines.h"

#include <gl_core_4_4.h>
#include <glfw\glfw3.h>


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
	return m_windowWidth;
}

unsigned int WindowEngine::Height() const
{
	return m_windowHeight;
}

float WindowEngine::AspectRatio() const
{
	return (float)m_windowWidth / (float)m_windowHeight;
}

void WindowEngine::SetTitle(const char * _title)
{
	glfwSetWindowTitle(m_window, _title);
}

void WindowEngine::SetWindowSize(unsigned int _width, unsigned int _height)
{
	m_windowWidth = _width;
	m_windowHeight = _height;
	glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);
}

void WindowEngine::Initialize()
{
	if (ENGINE::WINDOW != nullptr) LOG_ERROR("Attempted to Initialize WindowEngine multiple times.");

	ENGINE::WINDOW = new WindowEngine();

	ENGINE::WINDOW->SetWindowSize(800, 600);
	ENGINE::WINDOW->CreateOGLWindow();
	glfwSetWindowSizeCallback(ENGINE::WINDOW->m_window, WindowResizeCallback);
	glfwSetFramebufferSizeCallback(ENGINE::WINDOW->m_window, FrameBufferResizeCallback);
}

void WindowEngine::Finalize()
{
	if (ENGINE::WINDOW == nullptr) LOG_ERROR("Failed to Finalize WindowEngine.");

	ENGINE::WINDOW->DestroyOGLWindow();

	delete ENGINE::WINDOW;
}

WindowEngine::WindowEngine()
	: m_window()
	, m_title()
	, m_windowWidth()
	, m_windowHeight()
	, m_framebufferWidth()
	, m_framebufferHeight()
{
}

WindowEngine::~WindowEngine()
{
}

void WindowEngine::Core_EndFrame()
{
	// Swap Buffers
	glfwSwapBuffers(m_window);
	// Gather Window Inputs
	glfwPollEvents();
}

bool WindowEngine::Core_ShouldWindowClose()
{
	return glfwWindowShouldClose(m_window) != 0;
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
	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_title.c_str(), nullptr, nullptr);
	if (m_window == false) return false;

	// Create Context
	glfwMakeContextCurrent(m_window);

	// Load Functions
	InitialiseOGLFunctions();

	// Set Defaults. TODO MOVE TO RENDERENGINE
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

unsigned int WindowEngine::FrameBufferWidth() const
{
	return m_framebufferWidth;
}

unsigned int WindowEngine::FrameBufferHeight() const
{
	return m_framebufferHeight;
}

void WindowEngine::WindowResizeCallback(GLFWwindow * _window, int _width, int _height)
{
	ENGINE::WINDOW->m_windowWidth = _width;
	ENGINE::WINDOW->m_windowHeight = _height;
}

void WindowEngine::FrameBufferResizeCallback(GLFWwindow * _window, int _width, int _height)
{
	ENGINE::WINDOW->m_framebufferWidth = _width;
	ENGINE::WINDOW->m_framebufferHeight = _height;
}
