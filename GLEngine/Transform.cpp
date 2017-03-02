#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Transform.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

static const glm::vec3 Vector3::backward = glm::vec3(0, 0, -1);
static const glm::vec3 Vector3::down = glm::vec3(0, -1, 0);
static const glm::vec3 Vector3::forward = glm::vec3(0, 0, 1);
static const glm::vec3 Vector3::left = glm::vec3(-1, 0, 0);
static const glm::vec3 Vector3::one = glm::vec3(1, 1, 1);
static const glm::vec3 Vector3::right = glm::vec3(1, 0, 0);
static const glm::vec3 Vector3::up = glm::vec3(0, 1, 0);
static const glm::vec3 Vector3::zero = glm::vec3(0, 0, 0);

Transform::Transform()
	: position(0), orientation(), scale(1)
	, rotMatrix(1), localMatrix(1), worldMatrix(1), inverseMatrix(1)
	, invalidRotation(true), invalidLocal(true), invalidWorld(true), invalidInverse(true)
	, parent(this), children()
{
}

Transform::~Transform()
{
}

const glm::vec3 & Transform::LocalPosition()
{
	return position;
}

const glm::vec3 & Transform::LocalScale()
{
	return scale;
}

//const glm::vec3 & Transform::LocalRotation()
//{
//	return rotation;
//}

const glm::quat & Transform::LocalOrientation()
{
	return orientation;
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

glm::vec3 Transform::WorldPosition()
{
	return TransformPoint(LocalPosition());
}

//glm::vec3 Transform::WorldRotation()
//{
//	return TransformVector(LocalRotation());
//}

glm::vec3 Transform::WorldScale()
{
	return isRoot() ? LocalScale() : parent->WorldScale() * WorldScale();
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

glm::vec3 Transform::Up()
{
	return glm::normalize(TransformVector(Vector3::up));
}

glm::vec3 Transform::Right()
{
	return glm::normalize(TransformVector(Vector3::right));
}

glm::vec3 Transform::Forward()
{
	return glm::normalize(TransformVector(Vector3::forward));
}

glm::vec3 Transform::UpLocalAxis()
{
	return glm::vec3(RotMatrix()[1]);
}

glm::vec3 Transform::RightLocalAxis()
{
	return glm::vec3(RotMatrix()[0]);
}

glm::vec3 Transform::ForwardLocalAxis()
{
	return glm::vec3(RotMatrix()[2]);
}

bool Transform::isRoot() const
{
	return parent == this;
}

bool Transform::isChildOf(const Transform * const _parent) const
{
	return false;
}

void Transform::GetChildren(std::list<Transform*>& _outContainer)
{
	LOG_ERROR("INCOMPLETE.");
}

void Transform::GetChildrenCount(unsigned int & _outCount)
{
	LOG_ERROR("INCOMPLETE.");
}

void Transform::GetHierarchy(std::list<Transform*>& _outContainer)
{
	LOG_ERROR("INCOMPLETE.");
}

void Transform::GetHierarchyCount(unsigned int & _outCount)
{
	LOG_ERROR("INCOMPLETE.");
}

void Transform::Translate(const glm::vec3 & _vector)
{
	position += _vector;
	invalidLocal = true;
}

void Transform::Rotate(const glm::quat & _rot)
{
	orientation *= _rot;
	invalidRotation = true;
}

void Transform::Rotate(const glm::vec3 & _rot)
{
	Rotate(glm::quat(_rot));
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

void Transform::SetParent(Transform * _parent)
{
	if (parent != nullptr)
		parent->children.remove(this);

	parent = _parent;

	// Do maintain transform ? TODO

	if (_parent != nullptr)
		_parent->children.push_back(this);
}

void Transform::DetachChildren()
{
	for (auto iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->SetParent((*iter));
	}
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
	if (invalidLocal || invalidRotation)
	{
		CalculateLocal();
		invalidLocal = false;
	}
}

void Transform::ValidateWorld()
{
	if (invalidWorld || invalidLocal || invalidRotation)
	{
		CalculateWorld();
		invalidWorld = false;
	}
}

void Transform::ValidateInverse()
{
	if (invalidInverse || invalidWorld || invalidLocal || invalidRotation)
	{
		CalculateInverse();
		invalidInverse = false;
	}
}

void Transform::CalculateRotation()
{
	rotMatrix = glm::mat4_cast(orientation);

	//rotMatrix = glm::mat4(1);
	//rotMatrix = glm::rotate(rotMatrix, rotation.z, Vector3::forward);
	//rotMatrix = glm::rotate(rotMatrix, rotation.x, Vector3::right);
	//rotMatrix = glm::rotate(rotMatrix, rotation.y, Vector3::up);
}

void Transform::CalculateLocal()
{
	localMatrix = glm::mat4(1);
	localMatrix = glm::scale(localMatrix, scale);
	localMatrix *= RotMatrix();
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

void Transform::ClampRadians(const glm::vec3 & _source, glm::vec3 & _output) const
{
	static const float twoPi = glm::two_pi<float>();
	static const float min = 0.0f;
	_output = _source;
	while (_output.x >= twoPi) _output.x -= twoPi;
	while (_output.x < min) _output.x += twoPi;
	while (_output.y >= twoPi) _output.y -= twoPi;
	while (_output.y < min) _output.y += twoPi;
	while (_output.z >= twoPi) _output.z -= twoPi;
	while (_output.z < min) _output.z += twoPi;
}
