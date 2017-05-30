#include "RenderEngine.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "EngineDefines.h"


WindowManager * const RenderEngine::GetWindowManager()
{
	return &m_windowManager;
}

void RenderEngine::Initialize()
{
	if (ENGINE::RENDER() != nullptr) LOG_ERROR("Attempted to Initialize RenderEngine multiple times.");
	ENGINE::_internals::RENDER = new RenderEngine();
}

void RenderEngine::Finalize()
{
	if (ENGINE::RENDER() == nullptr) LOG_ERROR("Failed to Finalize RenderEngine.");



	delete ENGINE::RENDER();
}

RenderEngine::RenderEngine()
	: m_windowManager()
{
}

RenderEngine::~RenderEngine()
{
}
