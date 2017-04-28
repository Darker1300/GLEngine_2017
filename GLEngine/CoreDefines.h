#pragma once

class Core;
class TimeKeeper;
class RenderEngine;
class WindowEngine;
class InputEngine;
class ResourceEngine;
class SceneEngine;
class CameraEngine;
class LightEngine;

namespace ENGINE
{
	extern Core* CORE;
	extern TimeKeeper* TIME;
	extern RenderEngine* RENDER;
	extern WindowEngine* WINDOW;
	extern InputEngine* INPUT;
	extern ResourceEngine* RESOURCE;
	extern SceneEngine* SCENES;
	extern CameraEngine* CAMERAS;
	extern LightEngine* LIGHTS;
}
