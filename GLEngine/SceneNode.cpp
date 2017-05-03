#include "SceneNode.h"

#include <glm/ext.hpp>

SceneNode::SceneNode()
	: m_parent(nullptr)
	, m_children()
	, m_local(1.0f)
{
}

SceneNode::~SceneNode()
{
}

SceneNode * SceneNode::CreateChild()
{
	SceneNode* child = new SceneNode();
	m_children.push_back(child);
	child->m_parent = (SceneNode*)this;
	return child;
}

glm::mat4 SceneNode::World() const
{
	return glm::mat4();
}

void SceneNode::Translate(const glm::vec3 & _localUnits)
{
	m_local = glm::translate(m_local, _localUnits);
}

void SceneNode::Rotate(float _degrees, const glm::vec3 & _axis)
{
	m_local = glm::rotate(m_local, _degrees, _axis);
}

void SceneNode::Scale(const glm::vec3 & _multiplier)
{
	m_local = glm::scale(m_local, _multiplier);
}
