
#pragma once

class GameObject;

class Component
{
	friend class Scene;
public:
	Component(GameObject* _gameObject);
	virtual ~Component() {}

	virtual void Update() {}
	virtual void Render() {}

private:
	GameObject* gameObject;
};
