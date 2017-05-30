#pragma once

#include "ComponentManager.h"

class Camera;

class CameraManager
	: public ComponentManager<Camera>
{
public:
	CameraManager();
	~CameraManager();
};
