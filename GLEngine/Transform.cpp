#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Transform.h"

#include <glm/gtx/transform.hpp>

Transform::Transform()
	: position(0), rotation(0), scale(1), rotMatrix(1), worldMatrix(1), m_changed(true)
{
}


Transform::~Transform()
{
}

void Transform::Invalidate()
{
	m_changed = true;
}

glm::vec3 Transform::TransformPoint(const glm::vec3 & _point)
{
	return glm::vec3(WorldMatrix() * glm::vec4(_point, 1.0f));
}

glm::vec3 Transform::TransformVector(const glm::vec3 & _vector)
{
	return glm::vec3(RotMatrix() * glm::vec4(_vector, 0));
	//return Vector2(WorldMatrix() * Vector3(_vector, 0.0f));
}

glm::vec3 Transform::Up()
{
	return glm::normalize(TransformVector(Vector3::up));
}

glm::vec3 Transform::Right()
{
	return glm::normalize(TransformVector(Vector3::right));
}

glm::vec3 Transform::Forwards()
{
	return glm::vec3();
}

glm::mat4 & Transform::RotMatrix()
{
	UpdateMatrices();
	return rotMatrix;
}

glm::mat4 & Transform::WorldMatrix()
{
	UpdateMatrices();
	return worldMatrix;
}

void Transform::UpdateMatrices()
{
	if (m_changed)
	{
		RecalcMatrices();
		m_changed = false;
	}
}

void Transform::RecalcMatrices()
{
	// Rot
	//rotMatrix.SetZRotation(rotation);
	// rotQuat = glm::quat();//glm::rotate(glm::mat4(1), 0.0f, rotation);
	RecalcRotation();
	// glm::rotate();

	worldMatrix =
		glm::mat4(1)
		* glm::scale(scale)
		* rotMatrix
		* glm::translate(position);

	// Transform
//	worldMatrix[0] = rotMatrix[0] * scale.x;	worldMatrix[1] = rotMatrix[1];				worldMatrix[2] = 0.0f;
//	worldMatrix[3] = rotMatrix[2];				worldMatrix[4] = rotMatrix[3] * scale.y;	worldMatrix[5] = 0.0f;
//	worldMatrix[6] = position.x;				worldMatrix[7] = position.y;				worldMatrix[8] = 1.0f;
}

void Transform::RecalcRotation()
{
	rotMatrix = glm::mat4(1);
	rotMatrix = glm::rotate(rotMatrix, rotation.x, Vector3::right);
	rotMatrix = glm::rotate(rotMatrix, rotation.y, Vector3::up);
	rotMatrix = glm::rotate(rotMatrix, rotation.z, Vector3::forward);
	// glm::angleAxis();
	// rotMatrix = glm::quat(cos(glm::radians(90.0f / 2)), 0, sin(glm::radians(90.0f / 2)) * 1, 0);
}
