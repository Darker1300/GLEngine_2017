#pragma once

class Core;
class TimeKeeper;
class RenderEngine;
class WindowEngine;
class InputEngine;
class AssetEngine;
class SceneEngine;
class CameraManager;
class LightManager;

namespace ENGINE
{
	extern Core* CORE;
	extern TimeKeeper* TIME;
	extern RenderEngine* RENDER;
	extern WindowEngine* WINDOW;
	extern InputEngine* INPUT;
	extern AssetEngine* ASSETS;
	extern SceneEngine* SCENES;
	extern CameraManager* CAMERAS;
	extern LightManager* LIGHTS;
}
