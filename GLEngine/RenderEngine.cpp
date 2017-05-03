#include "RenderEngine.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "CoreDefines.h"



void RenderEngine::Initialize()
{
	if (ENGINE::RENDER != nullptr) LOG_ERROR("Attempted to Initialize RenderEngine multiple times.");
	ENGINE::RENDER = new RenderEngine();

}

void RenderEngine::Finalize()
{
	if (ENGINE::RENDER == nullptr) LOG_ERROR("Failed to Finalize RenderEngine.");



	delete ENGINE::RENDER;
}

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
}
