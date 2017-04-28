#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Core.h"

int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Core::Initialize();
	Core::Run();
	Core::Finalize();

#if _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
