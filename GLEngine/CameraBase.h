#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual void Update(float _deltaTime) {};

	void SetPosition(const glm::vec3& _pos);
	glm::vec3 GetPosition() const { return glm::vec3(m_worldTransform[3].x, m_worldTransform[3].y, m_worldTransform[3].z); }

	void LookAt(const glm::vec3& _eye, const glm::vec3& _center, const glm::vec3& _worldUp);
	void SetPerspective(float _vFOV, float _aspectRatio, float _nearDST, float _farDST);

	glm::mat4 GetTransform() const { return m_worldTransform; }
	void SetTransform(const glm::mat4& _trans);

	glm::mat4 GetView() const { return m_viewTransform; }
	glm::mat4 GetProjection() const { return m_projectionTransform; }
	glm::mat4 GetProjectionView() const { return m_projectionTransform * m_viewTransform; }

protected:
	void UpdateViewFromWorld();
	void UpdateWorldFromView();

#ifdef _DEBUG
	void PrintMat4(const glm::mat4& _transform) const;
#endif

	glm::mat4 m_worldTransform;

	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;
};

