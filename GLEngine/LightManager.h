#pragma once

#include "ComponentManager.h"

class Light;

class LightManager
	: public ComponentManager<Light>
{
public:
	LightManager();
	~LightManager();
};

