#include "DEGUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Camera.h"

#include "ApplicationBase.h"
#include <glm/ext.hpp>

Camera* GLE::MAIN_CAM = nullptr;

Camera::Camera()
{
	m_FOV = 0.25f;
	m_aspectRatio = (float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight();
	m_view = glm::lookAt(
		glm::vec3(30),
		glm::vec3(-5, 0, -5),
		glm::vec3(0, 1, 0));

	m_projection = glm::perspective(
		glm::pi<float>() * m_FOV, m_aspectRatio, 0.1f, 1000.0f);
}

Camera::Camera(float _fov, float _near, float _far, glm::vec3 _eye, glm::vec3 _center)
{
	m_FOV = _fov;
	m_aspectRatio = (float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight();
	m_view = glm::lookAt(_eye, _center, glm::vec3(0, 1, 0));

	m_projection = glm::perspective(
		glm::pi<float>() * m_FOV, m_aspectRatio, _near, _far);
}

Camera::Camera(float _fov, float _near, float _far, glm::mat4 _viewMatrix)
{
}

Camera::~Camera()
{
}

void Camera::SetAsMain()
{
	SetAsMain(this);
}

void Camera::SetAsMain(Camera * _camera)
{
	if (GLE::MAIN_CAM != nullptr)
		GLE::MAIN_CAM->OnLostFocus();

	GLE::MAIN_CAM = _camera;
	GLE::MAIN_CAM->OnGainFocus();
}

void Camera::SetPos(glm::vec3 _newPos)
{
	m_position = _newPos;
}

void Camera::SetDir(glm::vec3 _newDir)
{
	m_direction = _newDir;
}

void Camera::UpdateView()
{
	m_view = glm::lookAt(
		m_position,
		m_position + m_direction,
		glm::vec3(0, 1, 0));
}

void Camera::OnGainFocus()
{
}

void Camera::OnLostFocus()
{
}
