#pragma once

#include "Component.h"

class Light :
	public Component
{
	friend class Scene;
public:
	virtual ~Light();

protected:
	Light(GameObject* _gameObject);
};
