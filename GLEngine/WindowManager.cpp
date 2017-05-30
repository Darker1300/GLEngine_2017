
#include "WindowManager.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "EngineDefines.h"

#include <gl_core_4_4.h>
#include <glfw\glfw3.h>


WindowManager::WindowManager()
	: m_window()
	, m_title()
	, m_windowWidth()
	, m_windowHeight()
	, m_framebufferWidth()
	, m_framebufferHeight()
{
	SetWindowSize(800, 600);
	CreateOGLWindow();
	glfwSetWindowSizeCallback(m_window, WindowResizeCallback);
	glfwSetFramebufferSizeCallback(m_window, FrameBufferResizeCallback);
}

WindowManager::~WindowManager()
{
	DestroyOGLWindow();
}

GLFWwindow * WindowManager::Window() const
{
	return m_window;
}

std::string WindowManager::Title() const
{
	return m_title;
}

unsigned int WindowManager::Width() const
{
	return m_windowWidth;
}

unsigned int WindowManager::Height() const
{
	return m_windowHeight;
}

float WindowManager::AspectRatio() const
{
	return (float)m_windowWidth / (float)m_windowHeight;
}

void WindowManager::SetTitle(const char * _title)
{
	glfwSetWindowTitle(m_window, _title);
}

void WindowManager::SetWindowSize(unsigned int _width, unsigned int _height)
{
	m_windowWidth = _width;
	m_windowHeight = _height;
	glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);
}

void WindowManager::Core_EndFrame()
{
	// Swap Buffers
	glfwSwapBuffers(m_window);
	// Gather Window Inputs
	glfwPollEvents();
}

bool WindowManager::Core_ShouldWindowClose()
{
	return glfwWindowShouldClose(m_window) != 0;
}

bool WindowManager::InitialiseOGLFunctions()
{
	// Check LoadFunctions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		LOG_ERROR("OGL LoadFunctions Failed.")
			return false;
	}
	return true;
}

bool WindowManager::CreateOGLWindow()
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

void WindowManager::DestroyOGLWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

unsigned int WindowManager::FrameBufferWidth() const
{
	return m_framebufferWidth;
}

unsigned int WindowManager::FrameBufferHeight() const
{
	return m_framebufferHeight;
}

void WindowManager::WindowResizeCallback(GLFWwindow * _window, int _width, int _height)
{
	ENGINE::WINDOW()->m_windowWidth = _width;
	ENGINE::WINDOW()->m_windowHeight = _height;
}

void WindowManager::FrameBufferResizeCallback(GLFWwindow * _window, int _width, int _height)
{
	ENGINE::WINDOW()->m_framebufferWidth = _width;
	ENGINE::WINDOW()->m_framebufferHeight = _height;
}
