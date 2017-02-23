#include "CameraBase.h"

#ifdef _DEBUG
#include <iostream>
#endif

CameraBase::CameraBase()
	: m_worldTransform(1)
	, m_projectionTransform(1)
	, m_viewTransform(1)
{
	UpdateViewFromWorld();
}

CameraBase::~CameraBase()
{
}

void CameraBase::SetPosition(const glm::vec3 & _pos)
{
	m_worldTransform[3] = glm::vec4(_pos, 1);
	UpdateViewFromWorld();
}

void CameraBase::LookAt(const glm::vec3 & _eye, const glm::vec3 & _center, const glm::vec3 & _worldUp)
{
	//m_direction = glm::normalize(_center - _eye);
	m_viewTransform = glm::lookAt(_eye, _center, _worldUp);
	UpdateWorldFromView();
}

void CameraBase::SetPerspective(float _vFOV, float _aspectRatio, float _nearDST, float _farDST)
{
	m_projectionTransform = glm::perspective(_vFOV, _aspectRatio, _nearDST, _farDST);
}

void CameraBase::SetTransform(const glm::mat4 & _trans)
{
	m_worldTransform = _trans;
	UpdateViewFromWorld();
}

void CameraBase::UpdateViewFromWorld()
{
	m_viewTransform = glm::inverse(m_worldTransform);
}

void CameraBase::UpdateWorldFromView()
{
	m_worldTransform = glm::inverse(m_viewTransform);
}

#ifdef _DEBUG
void CameraBase::PrintMat4(const glm::mat4 & _transform) const
{
	std::cout
		<< " X: "
		<< _transform[0][0] << ','
		<< _transform[0][1] << ','
		<< _transform[0][2] << ','
		<< _transform[0][3] << ','
		<< " Y: "
		<< _transform[1][0] << ','
		<< _transform[1][1] << ','
		<< _transform[1][2] << ','
		<< _transform[1][3] << ','
		<< " Z: "
		<< _transform[2][0] << ','
		<< _transform[2][1] << ','
		<< _transform[2][2] << ','
		<< _transform[2][3] << ','
		<< " W: "
		<< _transform[3][0] << ','
		<< _transform[3][1] << ','
		<< _transform[3][2] << ','
		<< _transform[3][3] << ','
		<< std::endl;
}
#endif
