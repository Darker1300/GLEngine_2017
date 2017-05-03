
#pragma once

#include <vector>

class IComponent;
class SceneNode;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();
	void Render();

	SceneNode* m_sceneNode;
	std::vector<IComponent*> m_components;
};
