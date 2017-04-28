#pragma once

#include <string>

struct GLFWwindow;

class WindowEngine
{
	friend class Core;
	friend class RenderEngine;
public:
	static void Initialize();
	static void Finalize();

	GLFWwindow* Window() const;
	std::string Title() const;
	unsigned int Width() const;
	unsigned int Height() const;
	float AspectRatio() const;

	void SetTitle(const char* _title);
	void SetSize(unsigned int _width, unsigned int _height);

protected:
	WindowEngine();
	~WindowEngine();

	void Core_EndFrame();
	bool Core_ShouldWindowClose();

	bool InitialiseOGLFunctions();
	bool CreateOGLWindow();
	void DestroyOGLWindow();

	static void WindowSizeCallback(GLFWwindow* _window, int _width, int _height);

	GLFWwindow* m_window; 
	std::string m_title;
	unsigned int m_width;
	unsigned int m_height;
	bool m_sizeChanged;
};
