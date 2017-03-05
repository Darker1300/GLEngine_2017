#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Transform.h"

#include <glm/gtx/transform.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/quaternion.hpp>
#include <glm\ext.hpp>

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
	, localMatrix(1), worldMatrix(1), worldInverseMatrix(1), worldOrientation()
	, invalidLocal(true), invalidWorld(true), invalidWorldInverse(true), invalidWorldOrientation(true)
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

const glm::quat & Transform::LocalOrientation()
{
	return orientation;
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
	ValidateWorldInverse();
	return worldInverseMatrix;
}

const glm::quat & Transform::WorldOrientation()
{
	ValidateWorldOrientation();
	return worldOrientation;
}

glm::vec3 Transform::WorldPosition()
{
	return TransformPoint(LocalPosition());
}

glm::vec3 Transform::WorldScale()
{
	return isRoot() ? LocalScale() : parent->WorldScale() * LocalScale();
}

glm::vec3 Transform::TransformPoint(const glm::vec3 & _point)
{
	// UNSURE IF WORKING
	return glm::vec3(WorldMatrix() * glm::vec4(_point, 1.0f));
}

glm::vec3 Transform::TransformVector(const glm::vec3 & _vector)
{
	// UNSURE IF WORKING
	return glm::vec3(WorldMatrix() * glm::vec4(_vector, 0.0f));
}

glm::vec3 Transform::TransformDirection(const glm::vec3 & _direction)
{
	return _direction * WorldOrientation();
}

glm::vec3 Transform::InverseTransformPoint(const glm::vec3 & _point)
{
	// UNSURE IF WORKING
	return glm::vec3(LocalMatrix() * (InverseMatrix() * glm::vec4(_point, 1.0f)));
}

glm::vec3 Transform::InverseTransformVector(const glm::vec3 & _vector)
{
	// UNSURE IF WORKING
	return glm::vec3(LocalMatrix() * (InverseMatrix() * glm::vec4(_vector, 0.0f)));
}

glm::vec3 Transform::InverseTransformDirection(const glm::vec3 & _direction)
{
	// UNSURE IF WORKING
	return glm::vec3(LocalOrientation() * (glm::inverse(WorldOrientation()) * glm::vec4(_direction, 0.0f)));
}

glm::vec3 Transform::Up()
{
	return TransformDirection(Vector3::up);
}

glm::vec3 Transform::Right()
{
	return TransformDirection(Vector3::right);
}

glm::vec3 Transform::Forward()
{
	return TransformDirection(Vector3::forward);
}

bool Transform::isRoot() const
{
	return parent == this;
}

bool Transform::isChildOf(const Transform * const _parent) const
{
	if (parent == _parent) return true;
	else return (isRoot() ? false : parent->isChildOf(_parent));
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
	InvalidateLocal();
}

void Transform::Rotate(const glm::quat & _rot)
{
	orientation *= _rot;

	InvalidateLocal();
	InvalidateWorldOrientation();
}

void Transform::Rotate(const glm::vec3 & _rot)
{
	// Pitch
	if (_rot.z != 0.0f)
		orientation *= glm::angleAxis(_rot.z, Vector3::forward);
	// Yaw
	if (_rot.x != 0.0f)
		orientation *= glm::angleAxis(_rot.x, Vector3::right);
	// Roll
	if (_rot.y != 0.0f)
		orientation *= glm::angleAxis(_rot.y, Vector3::up);

	InvalidateLocal();
	InvalidateWorldOrientation();
}

void Transform::Scale(const glm::vec3 & _scalar)
{
	scale *= _scalar;
	InvalidateLocal();
}

void Transform::Scale(const float & _scalar)
{
	scale *= _scalar;
	InvalidateLocal();
}

void Transform::SetParent(Transform * _parent, bool _maintainTransform /*= true*/)
{
	if (parent != nullptr)
		parent->children.remove(this);

	// Maintain scale
	if (_maintainTransform) {
		scale = WorldScale() / _parent->WorldScale();
		InvalidateLocal();
		orientation = WorldOrientation() * glm::inverse(_parent->WorldOrientation());
		InvalidateLocal();
		InvalidateWorldOrientation();
	}

	parent = _parent;

	// Do maintain transform ? TODO

	if (_parent != nullptr)
		_parent->children.push_back(this);
}

void Transform::DetachChildren()
{
	for (auto iter = children.begin(); iter != children.end(); iter++)
		(*iter)->SetParent((*iter));
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
	if (invalidWorld || invalidLocal || invalidWorldOrientation)
	{
		CalculateWorld();
		invalidWorld = false;
	}
}

void Transform::ValidateWorldInverse()
{
	if (invalidWorldInverse)
	{
		CalculateWorldInverse();
		invalidWorldInverse = false;
	}
}

void Transform::ValidateWorldOrientation()
{
	if (invalidWorldOrientation)
	{
		CalculateWorldOrientation();
		invalidWorldOrientation = false;
	}
}

void Transform::InvalidateLocal()
{
	invalidLocal = true;
	invalidWorld = true;
	invalidWorldInverse = true;
	InvalidateChildren();
}

void Transform::InvalidateWorld()
{
	invalidWorld = true;
	invalidWorldInverse = true;
	InvalidateChildren();
}

void Transform::InvalidateWorldOrientation()
{
	invalidWorldOrientation = true;
}

void Transform::InvalidateChildren()
{
	for (auto iter = children.begin(); iter != children.end(); iter++)
		(*iter)->InvalidateWorld();
}

void Transform::CalculateLocal()
{
	localMatrix = glm::mat4(1);
	localMatrix = glm::scale(localMatrix, scale);
	localMatrix *= glm::mat4_cast(LocalOrientation());
	localMatrix = glm::translate(localMatrix, position);
}

void Transform::CalculateWorld()
{
	worldMatrix = isRoot() ? LocalMatrix() : parent->WorldMatrix() * LocalMatrix();
}

void Transform::CalculateWorldInverse()
{
	worldInverseMatrix = glm::inverse(WorldMatrix());
}

void Transform::CalculateWorldOrientation()
{
	worldOrientation = isRoot() ? LocalOrientation() : parent->WorldOrientation() * LocalOrientation();
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
