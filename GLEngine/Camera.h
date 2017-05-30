#pragma once
#include "Component.h"

class Camera :
	public Component
{
	friend class Scene;
public:
	virtual ~Camera();
protected:
	Camera(GameObject* _gameObject);
};
