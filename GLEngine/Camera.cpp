#include "Camera.h"



Camera::~Camera()
{
}

Camera::Camera(GameObject* _gameObject)
	: Component(_gameObject)
{
}