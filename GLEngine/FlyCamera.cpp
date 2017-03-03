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
	glm::vec3 move;
	glm::vec3 rotate;

#pragma region Movement
	// Forward
	if (glfwGetKey(m_window, GLFW_KEY_W)) {
		move += m_transform.TransformDirection(Vector3::forward);
	}
	// Backwards
	if (glfwGetKey(m_window, GLFW_KEY_S)) {
		move += m_transform.TransformDirection(Vector3::backward);
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_A)) {
		move += m_transform.TransformDirection(Vector3::right);
	}
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_D)) {
		move += m_transform.TransformDirection(Vector3::left);
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_E)) {
		move += m_transform.TransformDirection(Vector3::down);
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_Q)) {
		move += m_transform.TransformDirection(Vector3::up);
	}
#pragma endregion

#pragma region Rotation
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_KP_4)) {
		rotate += m_transform.TransformDirection(Vector3::down);
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_KP_6)) {
		rotate += m_transform.TransformDirection(Vector3::up);
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_KP_5)) {
		rotate += m_transform.TransformDirection(Vector3::right);
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_KP_8)) {
		rotate += m_transform.TransformDirection(Vector3::left);
	}
	// Roll Left
	if (glfwGetKey(m_window, GLFW_KEY_KP_7)) {
		rotate += m_transform.TransformDirection(Vector3::backward);
	}
	// Roll Right
	if (glfwGetKey(m_window, GLFW_KEY_KP_9)) {
		rotate += m_transform.TransformDirection(Vector3::forward);
	}

#pragma endregion

	float dirlength = glm::length(rotate);
	bool moved = glm::length(move) != 0.0f;
	bool rotated = dirlength != 0.0f;
	// Apply
	if (moved || rotated) {
		if (moved)
			m_transform.Translate(move * m_speed * _deltaTime);
		if (rotated)
			m_transform.Rotate(rotate * _deltaTime);
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
