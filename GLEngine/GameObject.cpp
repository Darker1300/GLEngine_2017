
#include "DEBUG_NEW_LEAK_DETECT.h"

#include "GameObject.h"

#include "Component.h"


GameObject::~GameObject()
{
	for each (Component* comp in m_components.m_collection) delete comp;
	m_components.Clear();
}

template<typename T>
inline T * const GameObject::CreateComponent() {
	(void)static_cast<Component*>((T*)0);
	return m_scene->CreateComponent<T>(this);
}

void GameObject::RemoveComponent(Component * _component)
{
	m_scene->RemoveComponent(_component);
	m_components.Remove(_component);
	delete _component;
}

void GameObject::RemoveComponents()
{
	for each (Component* comp in m_components.m_collection) {
		m_scene->RemoveComponent(comp);
		delete comp;
	}
	m_components.Clear();
}

GameObject::GameObject(Scene* const _scene)
	: m_scene(_scene)
	, m_components()
{
}
