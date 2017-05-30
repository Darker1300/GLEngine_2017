
#pragma once

#include <string>
#include <vector>
#include "LightManager.h"
#include "CameraManager.h"

class GameObject;
class Component;

class Scene
{
	friend class SceneEngine;
	friend class GameObject;

public:
	Scene();
	~Scene();

	LightManager*	const GetLightManager();
	CameraManager*	const GetCameraManager();

	GameObject* CreateGameObject();

protected:
	template<typename T>
	T* const CreateComponent(GameObject* _parent);
	template<>
	Light* const CreateComponent(GameObject* _parent);
	template<>
	Camera* const CreateComponent(GameObject* _parent);
	void const RemoveComponent(Component* _component);

	int m_buildIndex;
	std::string m_name;

	LightManager	m_lights;
	CameraManager	m_cameras;

	std::vector<GameObject*> m_objects;
};
