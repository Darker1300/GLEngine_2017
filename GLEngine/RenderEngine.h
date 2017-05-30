
#pragma once

#include "WindowManager.h"

class RenderEngine
{
	friend class Core;
public:

	WindowManager* const GetWindowManager();
protected:
	static void Initialize();
	static void Finalize();

	RenderEngine();
	~RenderEngine();

	WindowManager m_windowManager;
};
