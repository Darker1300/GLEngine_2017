#pragma once

class ApplicationBase;
namespace GLE {
	static ApplicationBase* APP = nullptr;
}

struct GLFWwindow;

class ApplicationBase
{
public:
	ApplicationBase(int _windowWidth, int _windowHeight);
	virtual ~ApplicationBase();

	void Run();
	// Run Calls
	virtual int Start() { return 0; }
	virtual int FixedUpdate(double _deltaTime) { return 0; }
	virtual int Update(double _deltaTime) { return 0; }
	virtual int LateUpdate(double _deltaTime) { return 0; }
	virtual int Draw() { return 0; }
	virtual int Shutdown() { return 0; }

	inline static void ERROR_MSG(const char* _msg);

	int GetWindowWidth();
	int GetWindowHeight();
	void GetOGLVersion(int& _outMajor, int& _outMinor);

protected:
	int m_windowWidth;
	int m_windowHeight;
	int m_GLMajor;
	int m_GLMinor;
	GLFWwindow* m_window;
};
