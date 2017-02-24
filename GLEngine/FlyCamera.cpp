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
	glm::vec4 vRight = glm::normalize(transform[0]);
	glm::vec4 vUp = glm::normalize(transform[1]);
	glm::vec4 vForward = glm::normalize(transform[2]);

	glm::vec4 moveDirection;
	glm::vec3 m_dir;

#pragma region Movement
	// Forwards
	if (glfwGetKey(m_window, GLFW_KEY_W)) {
		moveDirection -= (vForward * m_speed);
	}
	// Backwards
	if (glfwGetKey(m_window, GLFW_KEY_S)) {
		moveDirection += (vForward * m_speed);
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_A)) {
		moveDirection -= (vRight * m_speed);
	}
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_D)) {
		moveDirection += (vRight * m_speed);
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_E)) {
		moveDirection += (vUp * m_speed);
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_Q)) {
		moveDirection -= (vUp * m_speed);
	}
#pragma endregion

#pragma region Rotation
	// Left
	if (glfwGetKey(m_window, GLFW_KEY_KP_4)) {
		m_dir -= glm::vec3(1, 0, 0);
	}
	// Right
	if (glfwGetKey(m_window, GLFW_KEY_KP_6)) {
		m_dir += glm::vec3(1, 0, 0);
	}
	// Up
	if (glfwGetKey(m_window, GLFW_KEY_KP_5)) {
		m_dir -= glm::vec3(0, 1, 0);
	}
	// Down
	if (glfwGetKey(m_window, GLFW_KEY_KP_8)) {
		m_dir += glm::vec3(0, 1, 0);
	}
	//PrintMat4(transform);
#pragma endregion

	// Apply
	if (glm::length(moveDirection) > 0.0f)
	{
		transform[3] += moveDirection * _deltaTime;
		SetTransform(transform);
	}
	float dirlength = glm::length(m_dir);
	if (dirlength > 0.0f || dirlength < 0.0f)
	{
		m_transform.rotation += glm::normalize(m_dir) * _deltaTime * 100;

		//m_worldTransform = glm::inverse(m_transform.WorldMatrix());
		//UpdateViewFromWorld();
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
