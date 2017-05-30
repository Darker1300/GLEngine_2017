#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Scene.h"

#include "GameObject.h"
#include "Component.h"
#include "Light.h"
#include "Camera.h"


Scene::Scene()
{
}


Scene::~Scene()
{
	for each (GameObject* go in m_objects) delete go;
	m_objects.clear();

	m_lights.Clear();
	m_cameras.Clear();
}

LightManager * const Scene::GetLightManager()
{
	return &m_lights;
}

CameraManager * const Scene::GetCameraManager()
{
	return &m_cameras;
}

GameObject * Scene::CreateGameObject()
{
	GameObject* go = new GameObject(this);
	m_objects.push_back(go);
	return go;
}

template<typename T>
inline T * const Scene::CreateComponent(GameObject * _parent)
{
	(void)static_cast<Component*>((T*)0);

	T* comp = new T();
	return comp;
}
template<>
inline Light * const Scene::CreateComponent(GameObject * _parent) {
	Light* light = new Light(_parent);
	m_lights.Add(light);
	return light;
}
template<>
inline Camera* const Scene::CreateComponent(GameObject* _parent) {
	Camera* camera = new Camera(_parent);
	m_cameras.Add(camera);
	return camera;
}

void const Scene::RemoveComponent(Component * _component)
{
	if (dynamic_cast<Light*>(_component) != nullptr) {
		m_lights.Remove((Light*)_component);
	}
	if (dynamic_cast<Camera*>(_component) != nullptr) {
		m_cameras.Remove((Camera*)_component);
	}
}
