#pragma once

#include <glm\glm.hpp>

struct GLFWwindow;

class Camera;
namespace GLE { extern Camera* MAIN_CAM; }

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetProjectionViewMatrix();

	void SetClipping(float _near, float _far);
	void UpdateFly(GLFWwindow* _window, float _deltaTime, float _speed = 1.0f);

	glm::vec3 position;
	float m_yaw, m_pitch, m_roll;
	float m_FOV, m_aspectRatio, m_near, m_far;

private:
	glm::mat4 GetRotMatrix();
};
