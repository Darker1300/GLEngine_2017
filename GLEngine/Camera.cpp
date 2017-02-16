#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h> 
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Camera.h"

#include "ApplicationBase.h"
#include <glm/ext.hpp>

Camera::Camera()
{
	m_FOV = 25;
	m_aspectRatio = (float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight();
	m_view = glm::lookAt(
		glm::vec3(10, 10, 10),
		glm::vec3(0, 0, 0),
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

void Camera::OnGainFocus()
{
}

void Camera::OnLostFocus()
{
}
