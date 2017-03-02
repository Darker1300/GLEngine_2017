#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Transform.h"

class CameraBase;
namespace GLE { extern CameraBase* MAIN_CAM; }

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual void Update(float _deltaTime) {};

	// View
	// void LookAt(const glm::vec3& _eye, const glm::vec3& _center, const glm::vec3& _worldUp);
	// void LookAt(const glm::vec3& _target);

	// Perspective
	void SetPerspective(float _FOV, float _aspectRatio, float _nearDST, float _farDST);
	void SetFOV(const float _FOV);
	void SetAspectRatio(const float _aspectRatio);
	void SetNearFar(const float _nearDST, const float _farDST);

	void SetAsMain();
	static void SetAsMain(CameraBase* _camera);

	const glm::mat4& GetView() { return m_transform.InverseMatrix(); }
	const glm::mat4& GetProjection() const { return m_projectionTransform; }
	glm::mat4 GetProjectionViewWorld() { return GetProjection() * GetView() * m_transform.WorldMatrix(); }

	Transform m_transform;
protected:
	void CalculatePerspective();

	// Events
	virtual void OnGainFocus() {}
	virtual void OnLostFocus() {}

#ifdef _DEBUG
	void PrintMat4(const glm::mat4& _transform) const;
#endif
	glm::mat4 m_projectionTransform;

	float m_FOV, m_aspectRatio, m_near, m_far;
};
