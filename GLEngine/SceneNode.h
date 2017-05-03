
#pragma once

#include <vector>
#include <glm\glm.hpp>

class SceneNode
{
	friend class Scene;

protected:
	SceneNode();

public:
	~SceneNode();

	SceneNode* CreateChild() const;
	glm::mat4 World() const;

	void Translate(const glm::vec3& _localUnits);
	void Rotate(float _degrees, const glm::vec3& _axis);
	void Scale(const glm::vec3& _multiplier);
	
	std::vector<SceneNode*> m_children;
	glm::mat4 m_local;
};

