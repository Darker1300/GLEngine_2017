#pragma once

#include <glm/glm.hpp>

class Camera;
namespace GLE {
	static Camera* MAIN_CAM = nullptr;
}

class Camera
{
public:
	Camera();
	Camera(float _fov, float _near, float _far, glm::vec3 _eye, glm::vec3 _center);
	Camera(float _fov, float _near, float _far, glm::mat4 _viewMatrix);
	~Camera();

	void SetAsMain();
	static void SetAsMain(Camera* _camera);

	float m_FOV;
	float m_aspectRatio;
	glm::mat4 m_view;
	glm::mat4 m_projection;

protected:
	// Events
	virtual void OnGainFocus();
	virtual void OnLostFocus();
};
