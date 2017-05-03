
#pragma once

#include <string>

struct GLFWwindow;

class WindowEngine
{
	friend class Core;
	friend class RenderEngine;

public:
	GLFWwindow* Window() const;
	std::string Title() const;
	unsigned int Width() const;
	unsigned int Height() const;
	float AspectRatio() const;

	void SetTitle(const char* _title);
	void SetWindowSize(unsigned int _width, unsigned int _height);

protected:
	static void Initialize();
	static void Finalize();

	WindowEngine();
	~WindowEngine();

	void Core_EndFrame();
	bool Core_ShouldWindowClose();

	bool InitialiseOGLFunctions();
	bool CreateOGLWindow();
	void DestroyOGLWindow();

	unsigned int FrameBufferWidth() const;
	unsigned int FrameBufferHeight() const;

	static void WindowResizeCallback(GLFWwindow* _window, int _width, int _height);
	static void FrameBufferResizeCallback(GLFWwindow* _window, int _width, int _height);

	GLFWwindow* m_window; 
	std::string m_title;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;
	unsigned int m_framebufferWidth;
	unsigned int m_framebufferHeight;
};
