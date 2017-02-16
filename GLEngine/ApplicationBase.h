#pragma once

class ApplicationBase;
namespace GLE {
	static ApplicationBase* APP = nullptr;
}

struct GLFWwindow;

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	void Run(int _windowWidth, int _windowHeight);

	// Run Calls
	///<summary>Occurs once before Initialise.</summary>
	virtual int PreInitialise() { return 0; };
	///<summary>Occurs once before Start. OpenGL is Initialised along with the GLFWwindow.</summary>
	virtual int Initialise();
	///<summary>Occurs once before FixedUpdate, before main loop.</summary>
	virtual int Start() { return 0; }
	///<summary>Occurs before Update, Restricted to a consistent framerate. eg 60 FPS.</summary>
	virtual int FixedUpdate(double _deltaTime) { return 0; }
	///<summary>Occurs before LateUpdate.</summary>
	virtual int Update(double _deltaTime) { return 0; }
	///<summary>Occurs before Draw.</summary>
	virtual int LateUpdate(double _deltaTime) { return 0; }
	///<summary>Occurs at the end of main loop.</summary>
	virtual int Draw() { return 0; }
	///<summary>Occurs once before Finalise, after main loop has ended.</summary>
	virtual int Shutdown() { return 0; }
	///<summary>Occurs once after Shutdown.</summary>
	virtual int Finalise();

	int GetWindowWidth();
	int GetWindowHeight();
	void GetOGLVersion(int& _outMajor, int& _outMinor);
	///<summary>Frames Per a Second.</summary>
	int GetFPS();
	///<summary>Fixed Updates Per a Second.</summary>
	int GetFUPS();

protected:
	inline static void ERROR_MSG(const char* _msg);
	void InitialiseWindow();
	void FinaliseWindow();

	int m_windowWidth;
	int m_windowHeight;
	int m_GLMajor;
	int m_GLMinor;
	///<summary>Frames Per a Second.</summary>
	int m_FPS;
	///<summary>Fixed Updates Per a Second.</summary>
	int m_FUPS;
	double m_targetFPS;
	double m_fixedDTInterval;
	GLFWwindow* m_window;
};
