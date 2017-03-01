#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Transform.h"

#include <glm/gtx/transform.hpp>

static const glm::vec3 Vector3::back = glm::vec3(0, 0, -1);
static const glm::vec3 Vector3::down = glm::vec3(0, -1, 0);
static const glm::vec3 Vector3::forward = glm::vec3(0, 0, 1);
static const glm::vec3 Vector3::left = glm::vec3(-1, 0, 0);
static const glm::vec3 Vector3::one = glm::vec3(1, 1, 1);
static const glm::vec3 Vector3::right = glm::vec3(1, 0, 0);
static const glm::vec3 Vector3::up = glm::vec3(0, 1, 0);
static const glm::vec3 Vector3::zero = glm::vec3(0, 0, 0);

Transform::Transform()
	: position(0), rotation(0), scale(1)
	, rotMatrix(1), localMatrix(1), worldMatrix(1), inverseMatrix(1)
	, invalidRotation(true), invalidLocal(true), invalidWorld(true), invalidInverse(true)
	, parent(this), children()
{
}

Transform::~Transform()
{
}

glm::vec3 Transform::TransformPoint(const glm::vec3 & _point)
{
	return glm::vec3(WorldMatrix() * glm::vec4(_point, 1.0f));
}

glm::vec3 Transform::TransformVector(const glm::vec3 & _vector)
{
	return glm::vec3(WorldMatrix() * glm::vec4(_vector, 0.0f));
}

glm::vec3 Transform::InverseTransformPoint(const glm::vec3 & _point)
{
	return glm::vec3(LocalMatrix() * (InverseMatrix() * glm::vec4(_point, 1.0f)));
}

glm::vec3 Transform::InverseTransformVector(const glm::vec3 & _vector)
{
	return glm::vec3(LocalMatrix() * (InverseMatrix() * glm::vec4(_vector, 0.0f)));
}

void Transform::Rotate(const glm::vec3 & _rot)
{
	//TODO
	invalidRotation = true;
}

void Transform::Scale(const glm::vec3 & _scalar)
{
	scale *= _scalar;
	invalidLocal = true;
}

void Transform::Scale(const float & _scalar)
{
	scale *= _scalar;
	invalidLocal = true;
}

void Transform::Translate(const glm::vec3 & _vector)
{
	position += _vector;
	invalidLocal = true;
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

const glm::vec3 & Transform::LocalPosition()
{
	return position;
}

const glm::vec3 & Transform::LocalScale()
{
	return scale;
}

const glm::vec3 & Transform::LocalRotation()
{
	return rotation;
}

const glm::mat4 & Transform::RotMatrix()
{
	ValidateRotation();
	return rotMatrix;
}

const glm::mat4 & Transform::LocalMatrix()
{
	ValidateLocal();
	return localMatrix;
}

const glm::mat4 & Transform::WorldMatrix()
{
	ValidateWorld();
	return worldMatrix;
}

const glm::mat4 & Transform::InverseMatrix()
{
	ValidateInverse();
	return inverseMatrix;
}

bool Transform::isRoot() const
{
	return parent == this;
}

void Transform::ValidateRotation()
{
	if (invalidRotation)
	{
		CalculateRotation();
		invalidRotation = false;
	}
}

void Transform::ValidateLocal()
{
	if (invalidLocal)
	{
		CalculateLocal();
		invalidLocal = false;
	}
}

void Transform::ValidateWorld()
{
	if (invalidWorld)
	{
		CalculateWorld();
		invalidWorld = false;
	}
}

void Transform::ValidateInverse()
{
	if (invalidInverse)
	{
		CalculateInverse();
		invalidInverse = false;
	}
}

void Transform::CalculateRotation()
{
	rotMatrix = glm::mat4(1);
	rotMatrix = glm::rotate(rotMatrix, rotation.x, Vector3::right);
	rotMatrix = glm::rotate(rotMatrix, rotation.y, Vector3::up);
	rotMatrix = glm::rotate(rotMatrix, rotation.z, Vector3::forward);
}

void Transform::CalculateLocal()
{
	localMatrix = glm::mat4(1);
	localMatrix = glm::scale(localMatrix, scale);
	localMatrix *= rotMatrix;
	localMatrix = glm::translate(localMatrix, position);
}

void Transform::CalculateWorld()
{
	worldMatrix = isRoot() ? LocalMatrix() : parent->WorldMatrix() * LocalMatrix();
}

void Transform::CalculateInverse()
{
	inverseMatrix = glm::inverse(WorldMatrix());
}
