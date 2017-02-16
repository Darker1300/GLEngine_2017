#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "ApplicationDemo.h"

int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ApplicationBase* app = new ApplicationDemo();
	app->Run(1280, 720);
	delete app;

#if _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
