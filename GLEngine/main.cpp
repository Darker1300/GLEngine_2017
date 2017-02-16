//#include <gl_core_4_4.h>
//#include <GlFW/glfw3.h>
//
//#include <iostream>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include "Gizmos.h"

//#if defined(_WINDOWS_) && defined(_DEBUG)
//#include <Windows.h>
//#endif

#include "ApplicationBase.h"

int main()
{
	ApplicationBase* app = new ApplicationBase(1280, 720);
	app->Run();
	delete app;

	return 0;
}
