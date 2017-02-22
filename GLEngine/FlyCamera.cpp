#include "FlyCamera.h"

#include <glfw\glfw3.h>


FlyCamera::FlyCamera(GLFWwindow* _window, float _speed)
	: CameraBase()
	, m_speed(_speed)
	, m_window(_window)
{
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float _deltaTime)
{
	glm::mat4 transform = GetTransform();
	glm::vec4 vRight = transform[0];
	glm::vec4 vUp = transform[1];
	glm::vec4 vForward = transform[2];

	glm::vec4 moveDirection;

	// Forwards
	if (glfwGetKey(m_window, GLFW_KEY_W)) {
		moveDirection -= (vForward * m_speed);
	}
	// Backwards
	if (glfwGetKey(m_window, GLFW_KEY_S)) {
		moveDirection += (vForward * m_speed);
	}
	// Apply
	if (glm::length(moveDirection) > 0.0f)
	{
		transform[3] += moveDirection * _deltaTime;
		SetTransform(transform);
	}
}

void FlyCamera::SetSpeed(float _newSpeed)
{
	m_speed = _newSpeed;
}

float FlyCamera::GetSpeed() const
{
	return m_speed;
}
