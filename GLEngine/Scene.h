
#pragma once

#include <string>
#include <vector>

class LightManager;
class GameObject;

class Scene
{
	friend class SceneEngine;

public:
	Scene();
	~Scene();

protected:
	int m_buildIndex;
	std::string m_name;

	LightManager* m_lights;
	std::vector<GameObject*> m_objects;

};

