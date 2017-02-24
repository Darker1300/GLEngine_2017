#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class CameraBase;
namespace GLE { extern CameraBase* MAIN_CAM; }

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual void Update(float _deltaTime) {};

	void SetPosition(const glm::vec3& _pos);
	glm::vec3 GetPosition() const { return glm::vec3(m_worldTransform[3].x, m_worldTransform[3].y, m_worldTransform[3].z); }

	// View
	void LookAt(const glm::vec3& _eye, const glm::vec3& _center, const glm::vec3& _worldUp);


	// Perspective
	void SetPerspective(float _FOV, float _aspectRatio, float _nearDST, float _farDST);
	void SetFOV(const float _FOV);
	void SetAspectRatio(const float _aspectRatio);
	void SetNearFar(const float _nearDST, const float _farDST);

	void SetAsMain();
	static void SetAsMain(CameraBase* _camera);

	glm::mat4 GetTransform() const { return m_worldTransform; }
	void SetTransform(const glm::mat4& _trans);

	glm::mat4 GetView() const { return m_viewTransform; }
	glm::mat4 GetProjection() const { return m_projectionTransform; }
	glm::mat4 GetProjectionView() const { return m_projectionTransform * m_viewTransform; }

protected:
	void UpdateViewFromWorld();
	void UpdateWorldFromView();

	void UpdateView();
	void UpdatePerspective();

	// Events
	virtual void OnGainFocus() {}
	virtual void OnLostFocus() {}

#ifdef _DEBUG
	void PrintMat4(const glm::mat4& _transform) const;
#endif

	glm::mat4 m_worldTransform;

	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;

	float m_FOV, m_aspectRatio, m_near, m_far;
};
