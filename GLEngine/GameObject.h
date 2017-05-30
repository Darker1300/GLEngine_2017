
#pragma once

#include <vector>
#include "Scene.h"
#include "Transform.h"
#include "ComponentManager.h"

class GameObject
{
	friend class Scene;
	friend class Component;
public:
	typedef ComponentManager<Component> ComponentsManager;

	~GameObject();

	template<typename T>
	T* const CreateComponent();
	void RemoveComponent(Component* _component);
	void RemoveComponents();

	Transform transform;
protected:
	GameObject(Scene* const _scene);

	Scene* m_scene;
	ComponentsManager m_components;
};
