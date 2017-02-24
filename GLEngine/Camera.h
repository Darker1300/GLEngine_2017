#pragma once
//
//#include <glm/glm.hpp>
//
//class Camera;
//namespace GLE { extern Camera* MAIN_CAM; }
//
//class Camera
//{
//public:
//	Camera();
//	Camera(float _fov, float _near, float _far, glm::vec3 _eye, glm::vec3 _center);
//	Camera(float _fov, float _near, float _far, glm::mat4 _viewMatrix);
//	~Camera();
//
//	void SetAsMain();
//	static void SetAsMain(Camera* _camera);
//
//	void SetPos(glm::vec3 _newPos);
//	void SetDir(glm::vec3 _newDir);
//	void UpdateView();
//	
//	glm::vec3 m_position;
//	///<summary>Direction is a unit vector3.</summary>
//	glm::vec3 m_direction;
//
//	float m_FOV;
//	float m_aspectRatio;
//	glm::mat4 m_view;
//	glm::mat4 m_projection;
//
//protected:
//	// Events
//	virtual void OnGainFocus();
//	virtual void OnLostFocus();
//};
