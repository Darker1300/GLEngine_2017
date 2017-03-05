#include "Camera.h"

#include <glm\gtx\transform.hpp>
#include "Transform.h"
#include <glfw\glfw3.h>

Camera* GLE::MAIN_CAM = nullptr;

Camera::Camera()
	: position()
	, m_yaw(), m_pitch(), m_roll()
	, m_FOV(0.25f), m_aspectRatio(16.0f / 9.0f), m_near(0.001f), m_far(1000.0f)
{
}


Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::mat4 camera = glm::mat4();
	// translate
	camera = glm::translate(camera, position);

	// rotate around to a given bearing: yaw
	camera = glm::rotate(camera, m_yaw, Vector3::up);
	// rotate around to a given bearing: pitch
	camera = glm::rotate(camera, m_pitch, Vector3::right);
	// rotate around to a given bearing: roll
	camera = glm::rotate(camera, m_roll, Vector3::forward);

	// now get the view matrix by taking the rot inverse
	return glm::inverse(camera);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(
		glm::pi<float>() * m_FOV, m_aspectRatio, m_near, m_far);
}

glm::mat4 Camera::GetProjectionViewMatrix()
{
	return GetProjectionMatrix() * GetViewMatrix();
}

//void Camera::LookAt(const glm::vec3 & _point)
//{
//	forward = _point - position;
//}
//
//void Camera::Look(const glm::vec3 & _vector)
//{
//	forward = _vector;
//}

void Camera::SetClipping(float _near, float _far)
{
	m_near = _near;
	m_far = m_far;
}

void Camera::UpdateFly(GLFWwindow* _window, float _deltaTime, float _speed)
{
	glm::vec3 move = glm::vec3(0);
	glm::vec3 rotate = glm::vec3(0);

#pragma region Movement
	// Forward
	if (glfwGetKey(_window, GLFW_KEY_W)) {
		move -= Vector3::forward;
	}
	// Backwards
	if (glfwGetKey(_window, GLFW_KEY_S)) {
		move -= Vector3::backward;
	}
	// Right
	if (glfwGetKey(_window, GLFW_KEY_A)) {
		move += Vector3::left;
	}
	// Left
	if (glfwGetKey(_window, GLFW_KEY_D)) {
		move += Vector3::right;
	}
	// Up
	if (glfwGetKey(_window, GLFW_KEY_E)) {
		move += Vector3::up;
	}
	// Down
	if (glfwGetKey(_window, GLFW_KEY_Q)) {
		move += Vector3::down;
	}
#pragma endregion

#pragma region Rotation
	// Left
	if (glfwGetKey(_window, GLFW_KEY_KP_4)) {
		rotate -= Vector3::left;
	}
	// Right
	if (glfwGetKey(_window, GLFW_KEY_KP_6)) {
		rotate -= Vector3::right;
	}
	// Up
	if (glfwGetKey(_window, GLFW_KEY_KP_8)) {
		rotate += Vector3::up;
	}
	// Down
	if (glfwGetKey(_window, GLFW_KEY_KP_5)) {
		rotate += Vector3::down;
	}
	// Roll left
	if (glfwGetKey(_window, GLFW_KEY_KP_7)) {
		rotate += Vector3::forward;
	}
	// Roll right
	if (glfwGetKey(_window, GLFW_KEY_KP_9)) {
		rotate += Vector3::backward;
	}

#pragma endregion

	float dirlength = glm::length(rotate);
	bool moved = glm::length(move) != 0.0f;
	bool rotated = dirlength != 0.0f;
	// Apply
	if (moved || rotated) {
		if (moved)
			position += glm::vec3(GetRotMatrix() * glm::vec4(move, 0)) * _deltaTime * _speed;
		if (rotated) {
			m_yaw	+= rotate[0] * _deltaTime * _speed;
			m_pitch += rotate[1] * _deltaTime * _speed;
			m_roll	+= rotate[2] * _deltaTime * _speed;
		}
	}
}

glm::mat4 Camera::GetRotMatrix()
{
	glm::mat4 rot = glm::mat4();
	// roll
	rot = glm::rotate(rot, m_roll, Vector3::forward);
	// rotate around to a given bearing: yaw
	rot = glm::rotate(rot, m_yaw, Vector3::up);
	// the 'look up' axis, should be orthogonal to the up axis
	// rotate around to the required head tilt: pitch
	rot = glm::rotate(rot, m_pitch, Vector3::right);

	return rot;
}
