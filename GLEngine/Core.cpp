#include "Core.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "EngineDefines.h"

#include "TimeKeeper.h"
#include "RenderEngine.h"
#include "WindowManager.h"


void Core::Initialize()
{
	if (ENGINE::CORE() != nullptr) LOG_ERROR("Attempted to Initialize Core multiple times.");

	ENGINE::_internals::CORE = new Core();

	TimeKeeper::Initialize();
	RenderEngine::Initialize();
}

void Core::Finalize()
{
	if (ENGINE::CORE() == nullptr) LOG_ERROR("Failed to Finalize Core.");

	RenderEngine::Finalize();
	TimeKeeper::Finalize();

	delete ENGINE::CORE();
}

void Core::Run()
{
	// FPS TIMER
	float fpsTimer = 0;
	// ---------

	// Window Event: Close
	while (ENGINE::WINDOW()->Core_ShouldWindowClose() == false)
	{
		// Time Calculation
		ENGINE::TIME()->Core_StartFrame();

		while (ENGINE::TIME()->Core_FixedUpdateTick()) {
			// ~FIXED UPDATE~ HERE
		}

		// FPS TIMER
		fpsTimer += ENGINE::TIME()->DeltaTime();
		while (fpsTimer >= 0.1f) { fpsTimer -= 0.1f; printf(("FPS: " + std::to_string(ENGINE::TIME()->iFPS()) + +"\n").c_str()); }
		// ---------

		// Window Events
		ENGINE::WINDOW()->Core_EndFrame();
	}
}

Core::Core()
{
}

Core::~Core()
{
}
