
#include "EngineDefines.h"

#include "RenderEngine.h"
#include "SceneEngine.h"
#include "Scene.h"

Core*			ENGINE::_internals::CORE = nullptr;
TimeKeeper*		ENGINE::_internals::TIME = nullptr;
RenderEngine*	ENGINE::_internals::RENDER = nullptr;
InputEngine*	ENGINE::_internals::INPUT = nullptr;
AssetEngine*	ENGINE::_internals::ASSETS = nullptr;
SceneEngine*	ENGINE::_internals::SCENES = nullptr;

Core * const ENGINE::CORE()
{
	return ENGINE::_internals::CORE;
}

TimeKeeper * const ENGINE::TIME()
{
	return ENGINE::_internals::TIME;
}

RenderEngine * const ENGINE::RENDER()
{
	return ENGINE::_internals::RENDER;
}

WindowManager * const ENGINE::WINDOW()
{
	return ENGINE::_internals::RENDER->GetWindowManager();
}

InputEngine * const ENGINE::INPUT()
{
	return ENGINE::_internals::INPUT;
}

AssetEngine * const ENGINE::ASSETS()
{
	return ENGINE::_internals::ASSETS;
}

SceneEngine * const ENGINE::SCENES()
{
	return ENGINE::_internals::SCENES;
}

Scene * const ENGINE::SCENE()
{
	return ENGINE::_internals::SCENES->Active();
}

CameraManager * const ENGINE::CAMERAS()
{
	return ENGINE::_internals::SCENES->Active()->GetCameraManager();
}

LightManager * const ENGINE::LIGHTS()
{
	return ENGINE::_internals::SCENES->Active()->GetLightManager();
}
