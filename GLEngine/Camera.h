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

	// X:Yaw, Y:Pitch, Z:Roll. Rotated in following order: X, Y, Z
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetLocalMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetProjectionViewMatrix() { return GetProjectionMatrix() * GetViewMatrix(); }

	void SetClipping(float _near, float _far);
	void UpdateFly(GLFWwindow* _window, float _deltaTime, float _speed = 1.0f);

	inline static float ClampRadian(const float& _value);

	union {
		// Radians. X:Yaw, Y:Pitch, Z:Roll. Rotated in following order: X, Y, Z
		glm::vec3 forward;
		struct { float yaw, pitch, roll; };
	};
	glm::vec3 position;
	float m_FOV, m_aspectRatio, m_near, m_far;

private:
};
