#pragma once

class Core;
class TimeKeeper;
class RenderEngine;
class WindowManager;
class InputEngine;
class AssetEngine;
class SceneEngine;
class Scene;
class CameraManager;
class LightManager;

namespace ENGINE
{
	Core*			const CORE();
	TimeKeeper*		const TIME();
	RenderEngine*	const RENDER();
	WindowManager*	const WINDOW();
	InputEngine*	const INPUT();
	AssetEngine*	const ASSETS();
	SceneEngine*	const SCENES();
	Scene*			const SCENE();
	CameraManager*	const CAMERAS();
	LightManager*	const LIGHTS();

	namespace _internals {
		extern Core* CORE;
		extern TimeKeeper* TIME;
		extern RenderEngine* RENDER;
		extern InputEngine* INPUT;
		extern AssetEngine* ASSETS;
		extern SceneEngine* SCENES;
	}
}
