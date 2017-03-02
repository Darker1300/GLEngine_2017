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
	glm::vec3 m_move;
	glm::vec3 m_rotate;

#pragma region Movement
	// Forward
	if (glfwGetKey(m_window, GLFW_KEY_W)) {
		m_move += m_transform.LocalOrientation() * Vector3::forward;
	}
	// Backwards
	if (glfwGetKey(m_window, GLFW_KEY_S)) {
		m_move += m_transform.LocalOrientation() * Vector3::backward;
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_A)) {
		m_move += m_transform.LocalOrientation() * Vector3::right;
	}
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_D)) {
		m_move += m_transform.LocalOrientation() * Vector3::left;
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_E)) {
		m_move += Vector3::up;
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_Q)) {
		m_move += Vector3::down;
	}
#pragma endregion

#pragma region Rotation
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_KP_4)) {
		m_rotate += Vector3::down;
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_KP_6)) {
		m_rotate += Vector3::up;
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_KP_5)) {
		m_rotate += Vector3::right;
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_KP_8)) {
		m_rotate += Vector3::left;
	}

#pragma endregion

	float dirlength = glm::length(m_rotate);
	bool moved = glm::length(m_move) > 0.0f;
	bool rotated = dirlength > 0.0f || dirlength < 0.0f;
	// Apply
	if (moved || rotated) {
		if (moved)
			m_transform.Translate(m_move * m_speed * _deltaTime* 0.25f);
		if (rotated)
			m_transform.Rotate(m_rotate * _deltaTime * 0.5f);
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
