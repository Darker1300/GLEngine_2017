#include "DEBUG_NEW_LEAK_DETECT.h"

#include "Transform.h"

#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <algorithm>

static const glm::vec3 Vector3::back = glm::vec3(0, 0, -1);
static const glm::vec3 Vector3::down = glm::vec3(0, -1, 0);
static const glm::vec3 Vector3::forward = glm::vec3(0, 0, 1);
static const glm::vec3 Vector3::left = glm::vec3(-1, 0, 0);
static const glm::vec3 Vector3::one = glm::vec3(1, 1, 1);
static const glm::vec3 Vector3::right = glm::vec3(1, 0, 0);
static const glm::vec3 Vector3::up = glm::vec3(0, 1, 0);
static const glm::vec3 Vector3::zero = glm::vec3(0, 0, 0);

Transform::Transform()
	: m_positionLocal(0), m_orientationLocal(0, 0, 0, 1), m_scaleLocal(1)
	, m_transformLocalMatrix(1), m_transformWorldMatrix(1), m_transformInverseWorldMatrix(1)
	, m_changedLocalTransform(true), m_changedWorldTransform(true), m_changedInverseWorldTransform(true)
	, parent(this), children()
{
}



//Transform::Transform(const Transform & _other)
//	: m_positionLocal(_other.m_positionLocal), m_translateLocalMatrix(_other.m_translateLocalMatrix)
//	, m_rotationLocal(_other.m_rotationLocal), m_orientationLocal(_other.m_orientationLocal), m_rotationLocalMatrix(_other.m_rotationLocalMatrix)
//	, m_scaleLocal(_other.m_scaleLocal), m_scaleLocalMatrix(_other.m_scaleLocalMatrix)
//	, m_transformLocalMatrix(_other.m_transformLocalMatrix), m_transformWorldMatrix(_other.m_transformWorldMatrix), m_transformInverseWorldMatrix(_other.m_transformInverseWorldMatrix)
//	, m_changedTranslationMatrix(_other.m_changedTranslationMatrix), m_changedRotationMatrix(_other.m_changedRotationMatrix), m_changedScaleMatrix(_other.m_changedScaleMatrix)
//	, m_changedLocalTransform(_other.m_changedLocalTransform), m_changedWorldTransform(_other.m_changedWorldTransform), m_changedInverseWorldTransform(_other.m_changedInverseWorldTransform)
//	, parent(_other.parent), children(_other.children)
//{
//}
//
//Transform::Transform(Transform && _other)
//	: m_positionLocal(_other.m_positionLocal), m_translateLocalMatrix(_other.m_translateLocalMatrix)
//	, m_rotationLocal(_other.m_rotationLocal), m_orientationLocal(_other.m_orientationLocal), m_rotationLocalMatrix(_other.m_rotationLocalMatrix)
//	, m_scaleLocal(_other.m_scaleLocal), m_scaleLocalMatrix(_other.m_scaleLocalMatrix)
//	, m_transformLocalMatrix(_other.m_transformLocalMatrix), m_transformWorldMatrix(_other.m_transformWorldMatrix), m_transformInverseWorldMatrix(_other.m_transformInverseWorldMatrix)
//	, m_changedTranslationMatrix(_other.m_changedTranslationMatrix), m_changedRotationMatrix(_other.m_changedRotationMatrix), m_changedScaleMatrix(_other.m_changedScaleMatrix)
//	, m_changedLocalTransform(_other.m_changedLocalTransform), m_changedWorldTransform(_other.m_changedWorldTransform), m_changedInverseWorldTransform(_other.m_changedInverseWorldTransform)
//	, parent(_other.parent), children(_other.children)
//{
//}
//
//Transform::~Transform()
//{
//}
//
//Transform & Transform::operator=(const Transform & _other)
//{
//	// T
//	m_positionLocal = _other.m_positionLocal;
//	m_translateLocalMatrix = _other.m_translateLocalMatrix;
//	// R
//	m_rotationLocal = _other.m_rotationLocal;
//	m_orientationLocal = _other.m_orientationLocal;
//	m_rotationLocalMatrix = _other.m_rotationLocalMatrix;
//	// S
//	m_scaleLocal = _other.m_scaleLocal;
//	m_scaleLocalMatrix = _other.m_scaleLocalMatrix;
//	// Tf
//	m_transformLocalMatrix = _other.m_transformLocalMatrix;
//	m_transformWorldMatrix = _other.m_transformWorldMatrix;
//	m_transformInverseWorldMatrix = _other.m_transformInverseWorldMatrix;
//	// Flags
//	m_changedTranslationMatrix = _other.m_changedTranslationMatrix;
//	m_changedRotationMatrix = _other.m_changedRotationMatrix;
//	m_changedScaleMatrix = _other.m_changedScaleMatrix;
//	m_changedLocalTransform = _other.m_changedLocalTransform;
//	m_changedWorldTransform = _other.m_changedWorldTransform;
//	m_changedInverseWorldTransform = _other.m_changedInverseWorldTransform;
//	// Hierarchy
//	parent = _other.parent;
//	children = _other.children;
//	return *this;
//}
//
//Transform & Transform::operator=(Transform && _other)
//{
//	// T
//	m_positionLocal = _other.m_positionLocal;
//	m_translateLocalMatrix = _other.m_translateLocalMatrix;
//	// R
//	m_rotationLocal = _other.m_rotationLocal;
//	m_orientationLocal = _other.m_orientationLocal;
//	m_rotationLocalMatrix = _other.m_rotationLocalMatrix;
//	// S
//	m_scaleLocal = _other.m_scaleLocal;
//	m_scaleLocalMatrix = _other.m_scaleLocalMatrix;
//	// Tf
//	m_transformLocalMatrix = _other.m_transformLocalMatrix;
//	m_transformWorldMatrix = _other.m_transformWorldMatrix;
//	m_transformInverseWorldMatrix = _other.m_transformInverseWorldMatrix;
//	// Flags
//	m_changedTranslationMatrix = _other.m_changedTranslationMatrix;
//	m_changedRotationMatrix = _other.m_changedRotationMatrix;
//	m_changedScaleMatrix = _other.m_changedScaleMatrix;
//	m_changedLocalTransform = _other.m_changedLocalTransform;
//	m_changedWorldTransform = _other.m_changedWorldTransform;
//	m_changedInverseWorldTransform = _other.m_changedInverseWorldTransform;
//	// Hierarchy
//	parent = _other.parent;
//	children = _other.children;
//	return *this;
//}
//
//#pragma region Utility
//
//glm::vec4 Transform::TransformPoint(const glm::vec4 & _point)
//{
//	return WorldMatrix() * _point;
//}
//
//glm::vec3 Transform::TransformPoint(const glm::vec3 & _point)
//{
//	return glm::vec3(TransformPoint(glm::vec4(_point, 1.0f)));
//}
//
//glm::vec4 Transform::TransformVector(const glm::vec4 & _vector)
//{
//	return WorldMatrix() * _vector;
//}
//
//glm::vec3 Transform::TransformVector(const glm::vec3 & _vector)
//{
//	return glm::vec3(TransformVector(glm::vec4(_vector, 0.0f)));
//}
//
//glm::vec4 Transform::TransformScalar(const glm::vec4 & _scalar)
//{
//	return glm::vec4();
//}
//
//glm::vec3 Transform::TransformScalar(const glm::vec3 & _scalar)
//{
//	return glm::vec3(TransformScalar(glm::vec4(_scalar, 1.0f)));
//}
//
//glm::vec4 Transform::InverseTransformPoint(const glm::vec4 & _point)
//{
//	return LocalMatrix() * (InverseWorldMatrix() *  _point);
//}
//
//glm::vec3 Transform::InverseTransformPoint(const glm::vec3 & _point)
//{
//	return glm::vec3(InverseTransformPoint(glm::vec4(_point, 1.0f)));
//}
//
//glm::vec4 Transform::InverseTransformVector(const glm::vec4 & _vector)
//{
//	return LocalMatrix() * (InverseWorldMatrix() *  _vector);
//}
//
//glm::vec3 Transform::InverseTransformVector(const glm::vec3 & _vector)
//{
//	return glm::vec3(InverseTransformVector(glm::vec4(_vector, 0.0f)));
//}
//
//glm::vec4 Transform::InverseTransformScalar(const glm::vec4 & _scalar)
//{
//	return glm::vec4();
//}
//
//glm::vec3 Transform::InverseTransformScalar(const glm::vec3 & _scalar)
//{
//	return glm::vec3(InverseTransformScalar(glm::vec4(_scalar, 1.0f)));
//}
//
//glm::vec3 Transform::Up()
//{
//	return glm::normalize(TransformVector(Vector3::up));
//}
//
//glm::vec3 Transform::Right()
//{
//	return glm::normalize(TransformVector(Vector3::right));
//}
//
//glm::vec3 Transform::Forwards()
//{
//	return glm::normalize(TransformVector(Vector3::forward));
//}
//
//void Transform::SetParent(Transform * _parent)
//{
//	if (parent != nullptr)
//		parent->RemoveChild(this);
//
//	parent = _parent;
//
//	if (_parent != nullptr)
//		_parent->AddChild(this);
//}
//
//bool Transform::isTopOfHierarchy() const
//{
//	return parent == nullptr;
//}
//
//bool Transform::isChildOf(Transform * _parent)
//{
//	return false;
//}
//
//void Transform::AddChild(Transform * _child)
//{
//	children.push_back(_child);
//}
//
//void Transform::RemoveChild(Transform * _child)
//{
//	children.remove(_child);
//}
//
//bool Transform::RemoveChildFromChildren(Transform * _child)
//{
//	auto iter = std::find(children.begin(), children.end(), _child);
//	bool found = (iter != children.end());
//	if (found) {
//		children.erase(iter);
//		return true;
//	}
//	for (auto iter = children.begin(); iter != children.end(); iter++)
//		if ((*iter)->RemoveChildFromChildren(_child) == true)
//			return true;
//	return false;
//}
//
//Transform * Transform::GetRoot()
//{
//	return isTopOfHierarchy() ? this : parent->GetRoot();
//}
//
//std::list<Transform*> Transform::GetChildren()
//{
//	return std::list<Transform*>(children);
//}
//
//void Transform::GetHierarchy(std::list<Transform*>& _container)
//{
//	_container.push_back(this);
//	for (auto iter = children.begin(); iter != children.end(); iter++)
//		(*iter)->GetHierarchy(_container);
//}
//
//void Transform::GetHierarchyCount(unsigned int& _count)
//{
//	_count++;
//	for (auto iter = children.begin(); iter != children.end(); iter++)
//		(*iter)->GetHierarchyCount(_count);
//}
//
//#pragma endregion Utility
//
//#pragma region Getters
//
//const glm::vec3 & Transform::LocalPosition()
//{
//	return m_positionLocal;
//}
//
//const glm::mat4 & Transform::LocalTranslateMatrix()
//{
//	if (m_changedTranslationMatrix) { CalcTranslationMatrix(); }
//	return m_translateLocalMatrix;
//}
//
//const glm::vec3 & Transform::LocalScale()
//{
//	return m_scaleLocal;
//}
//
//const glm::mat4 & Transform::LocalScaleMatrix()
//{
//	if (m_changedScaleMatrix) { CalcScaleMatrix(); }
//	return m_scaleLocalMatrix;
//}
//
//const glm::vec3 & Transform::LocalRotation()
//{
//	return m_rotationLocal;
//}
//
//const glm::quat & Transform::LocalOrientation()
//{
//	return m_orientationLocal;
//}
//
//const glm::mat4 & Transform::LocalRotationMatrix()
//{
//	if (m_changedRotationMatrix) { CalculateRotationMatrix(); }
//	return m_rotationLocalMatrix;
//}
//
//const glm::mat4 & Transform::LocalMatrix()
//{
//	if (m_changedLocalTransform) { CalculateLocalTransform(); }
//	return m_transformLocalMatrix;
//}
//
//glm::vec3 Transform::WorldPosition()
//{
//	return InverseTransformPoint(LocalPosition());
//}
//
//glm::vec3 Transform::WorldRotation()
//{
//	return InverseTransformVector(LocalRotation());
//}
//
//glm::vec3 Transform::WorldScale()
//{
//	return InverseTransformScalar(LocalScale());
//}
//
//const glm::mat4 & Transform::WorldMatrix()
//{
//	if (m_changedWorldTransform) { CalculateWorldTransform(); }
//	return m_transformWorldMatrix;
//}
//
//const glm::mat4 & Transform::InverseWorldMatrix()
//{
//	if (m_changedInverseWorldTransform) { CalculateInverseWorldTransform(); }
//	return m_transformInverseWorldMatrix;
//}
//
//#pragma endregion Getters
//
//#pragma region Setters
//
//void Transform::SetLocalPosition(const glm::vec3 & _pos)
//{
//	// Set this
//	m_positionLocal = _pos;
//	// Set flag forwards
//	InvalidateTranslationMatrix();
//}
//
//void Transform::SetLocalTranslateMatrix(const glm::mat4 & _mat)
//{
//	// Set this
//	m_translateLocalMatrix = _mat;
//	// Set backwards
//	m_positionLocal = glm::vec3(m_translateLocalMatrix[3]);
//
//	// Clear flag this
//	m_changedTranslationMatrix = false;
//	// Set flag forwards
//	InvalidateTransformMatrix();
//}
//
//void Transform::SetLocalRotation(const glm::vec3 & _rot)
//{
//	// Set this
//	m_rotationLocal = _rot;
//	// Set forwards
//	Math::CalculateRotation(m_rotationLocal, m_orientationLocal);
//
//	// Set flag forwards
//	InvalidateRotationMatrix();
//}
//
//void Transform::SetLocalOrientation(const glm::quat & _quat)
//{
//	// Set this
//	m_orientationLocal = _quat;
//	// Set backwards
//	Math::CalculateRotation(m_orientationLocal, m_rotationLocal);
//
//	// Set flag forwards
//	InvalidateRotationMatrix();
//}
//
//void Transform::SetLocalRotationMatrix(const glm::mat4 & _mat)
//{
//	// Set this
//	m_rotationLocalMatrix = _mat;
//	// Set backwards
//	Math::CalculateRotation(m_rotationLocalMatrix, m_orientationLocal);
//	Math::CalculateRotation(m_orientationLocal, m_rotationLocal);
//
//	// Clear flag this
//	m_changedRotationMatrix = false;
//	// Set flag forwards
//	InvalidateTransformMatrix();
//}
//
//void Transform::SetLocalScale(const glm::vec3 & _scale)
//{
//	// Set this
//	m_scaleLocal = _scale;
//	// Set flag forwards
//	InvalidateScaleMatrix();
//}
//
//void Transform::SetLocalScaleMatrix(const glm::mat4 & _mat)
//{
//	// Set this
//	m_scaleLocalMatrix = _mat;
//	// Set backwards
//	m_scaleLocal = glm::vec3(m_scaleLocalMatrix[0][0], m_scaleLocalMatrix[1][1], m_scaleLocalMatrix[2][2]);
//
//	// Clear flag this
//	m_changedScaleMatrix = false;
//	// Set flag forwards
//	InvalidateTransformMatrix();
//}
//
//void Transform::SetWorldPosition(const glm::vec3 & _pos)
//{
//}
//
//void Transform::SetWorldRotation(const glm::vec3 & _rot)
//{
//}
//
//void Transform::SetWorldScale(const glm::vec3 & _scale)
//{
//}
//
//#pragma endregion Setters
//
//#pragma region Invalidate
//
//void Transform::InvalidateTranslationMatrix()
//{
//	m_changedTranslationMatrix = true;
//	InvalidateTransformMatrix();
//}
//
//void Transform::InvalidateRotationMatrix()
//{
//	m_changedRotationMatrix = true;
//	InvalidateTransformMatrix();
//}
//
//void Transform::InvalidateScaleMatrix()
//{
//	m_changedScaleMatrix = true;
//}
//
//void Transform::InvalidateTransformMatrix()
//{
//	m_changedLocalTransform = true;
//	InvalidateWorldTransformMatrix();
//}
//
//void Transform::InvalidateWorldTransformMatrix()
//{
//	m_changedWorldTransform = true;
//	InvalidateInverseWorldTransformMatrix();
//}
//
//void Transform::InvalidateInverseWorldTransformMatrix()
//{
//	m_changedInverseWorldTransform = true;
//}
//
//#pragma endregion Invalidate
//
//#pragma region Calculation Helpers
//
//void Transform::CalcTranslationMatrix()
//{
//	m_translateLocalMatrix = glm::translate(m_positionLocal);
//	m_changedTranslationMatrix = false;
//}
//
//void Transform::CalcScaleMatrix()
//{
//	m_scaleLocalMatrix = glm::scale(m_scaleLocal);
//	m_changedScaleMatrix = false;
//}
//
//void Transform::CalculateRotationMatrix()
//{
//	Math::CalculateRotation(LocalOrientation(), m_rotationLocalMatrix);
//	m_changedRotationMatrix = false;
//}
//
//void Transform::CalculateLocalTransform()
//{
//	m_transformLocalMatrix = glm::mat4(1)
//		* LocalScaleMatrix()
//		* LocalRotationMatrix()
//		* LocalTranslateMatrix();
//	m_changedLocalTransform = false;
//}
//
//void Transform::CalculateWorldTransform()
//{
//	// TODO
//	m_transformWorldMatrix = LocalMatrix();
//	m_changedWorldTransform = false;
//}
//
//void Transform::CalculateInverseWorldTransform()
//{
//	m_transformInverseWorldMatrix = glm::inverse(WorldMatrix());
//	m_changedInverseWorldTransform = false;
//}
//
//#pragma endregion Calculation Helpers
//
//#pragma region Math Helpers
//
//void Transform::Math::CalculateRotation(const glm::vec3 & _eulers, glm::quat & _outQuat)
//{
//	float halfPitch = _eulers.x * 0.5f;
//	float sinPitch = glm::sin(halfPitch);
//	float cosPitch = glm::cos(halfPitch);
//
//	float halfYaw = _eulers.y * 0.5f;
//	float sinYaw = glm::sin(halfYaw);
//	float cosYaw = glm::cos(halfYaw);
//
//	float halfRoll = _eulers.z * 0.5f;
//	float sinRoll = glm::sin(halfRoll);
//	float cosRoll = glm::cos(halfRoll);
//
//	_outQuat.x = ((cosYaw * sinPitch) * cosRoll) + ((sinYaw * cosPitch) * sinRoll);
//	_outQuat.y = ((sinYaw * cosPitch) * cosRoll) - ((cosYaw * sinPitch) * sinRoll);
//	_outQuat.z = ((cosYaw * cosPitch) * sinRoll) - ((sinYaw * sinPitch) * cosRoll);
//	_outQuat.w = ((cosYaw * cosPitch) * cosRoll) + ((sinYaw * sinPitch) * sinRoll);
//}
//
//void Transform::Math::CalculateRotation(const glm::quat & _quat, glm::vec3 & _outEulers)
//{
//	// roll
//	_outEulers.z = std::atan2f(
//		2 * (_quat.x*_quat.y + _quat.z*_quat.w),
//		(1 - 2 * (_quat.y*_quat.y + _quat.z*_quat.z)));
//	// pitch
//	_outEulers.x = std::asinf(2 * (_quat.x*_quat.z - _quat.w*_quat.y));
//	// yaw
//	_outEulers.y = std::atan2f(
//		2 * (_quat.x*_quat.w + _quat.y*_quat.z),
//		(1 - 2 * (_quat.z*_quat.z + _quat.w*_quat.w)));
//}
//
//void Transform::Math::CalculateRotation(const glm::vec3 & _eulers, glm::mat4 & _outMat4)
//{
//	_outMat4 = glm::eulerAngleXYZ(_eulers.x, _eulers.y, _eulers.z);
//}
//
//void Transform::Math::CalculateRotation(const glm::quat & _quat, glm::mat4 & _outMat4)
//{
//	_outMat4 = glm::toMat4(_quat);
//}
//
//void Transform::Math::CalculateRotation(const glm::mat4 & _mat4, glm::quat & _outQuat)
//{
//	_outQuat = glm::quat_cast(_mat4);
//}
//
//#pragma endregion Math Helpers


//void Transform::Math::Convert(const glm::vec3 & _eulers, glm::quat & _outQuat)
//{
//	float halfPitch = _eulers.x * 0.5f;
//	float sinPitch = glm::sin(halfPitch);
//	float cosPitch = glm::cos(halfPitch);
//
//	float halfYaw = _eulers.y * 0.5f;
//	float sinYaw = glm::sin(halfYaw);
//	float cosYaw = glm::cos(halfYaw);
//
//	float halfRoll = _eulers.z * 0.5f;
//	float sinRoll = glm::sin(halfRoll);
//	float cosRoll = glm::cos(halfRoll);
//
//	_outQuat.x = ((cosYaw * sinPitch) * cosRoll) + ((sinYaw * cosPitch) * sinRoll);
//	_outQuat.y = ((sinYaw * cosPitch) * cosRoll) - ((cosYaw * sinPitch) * sinRoll);
//	_outQuat.z = ((cosYaw * cosPitch) * sinRoll) - ((sinYaw * sinPitch) * cosRoll);
//	_outQuat.w = ((cosYaw * cosPitch) * cosRoll) + ((sinYaw * sinPitch) * sinRoll);
//}
//
//void Transform::Math::Convert(const glm::quat & _quat, glm::vec3 & _outEulers)
//{
//	// roll
//	_outEulers.z = std::atan2f(
//		2 * (_quat.x*_quat.y + _quat.z*_quat.w),
//		(1 - 2 * (_quat.y*_quat.y + _quat.z*_quat.z)));
//	// pitch
//	_outEulers.x = std::asinf(2 * (_quat.x*_quat.z - _quat.w*_quat.y));
//	// yaw
//	_outEulers.y = std::atan2f(
//		2 * (_quat.x*_quat.w + _quat.y*_quat.z),
//		(1 - 2 * (_quat.z*_quat.z + _quat.w*_quat.w)));
//}


void Transform::SetLocalOrientation(const glm::quat & _quat)
{
}

void Transform::SetLocalRotation(const glm::vec3 & _rot)
{
	SetLocalOrientation(glm::quat_cast(glm::eulerAngleXYZ(_rot.x, _rot.y, _rot.z)));
	// glm::vec3 lookAtPt = direction;
	// glm::mat4 rotMatrix = glm::lookAt(glm::vec3(0), lookAtPt, up);
	// glm::quat rotation = glm::quat_cast(rotMatrix);

}

void Transform::SetWorldOrientation(const glm::quat & _quat)
{
}

void Transform::SetWorldRotation(const glm::vec3 & _rot)
{
}

void Transform::InvalidateLocalMatrix()
{
	m_changedLocalTransform = true;
	InvalidateWorldMatrix();
}

void Transform::InvalidateWorldMatrix()
{
	m_changedWorldTransform = true;
	InvalidateInverseWorldMatrix();
}

void Transform::InvalidateInverseWorldMatrix()
{
	m_changedInverseWorldTransform = true;
}

glm::vec4 Transform::TransformPoint(const glm::vec4 & _point)
{
	return WorldOrientation() * _point;
}

glm::vec3 Transform::TransformPoint(const glm::vec3 & _point)
{
	return glm::vec3(TransformPoint(glm::vec4(_point, 1)));
}

glm::vec4 Transform::TransformVector(const glm::vec4 & _vector)
{
	return WorldOrientation() * _vector;
}

glm::vec3 Transform::TransformVector(const glm::vec3 & _vector)
{
	return glm::vec3(TransformVector(glm::vec4(_vector, 1)));
}

glm::quat Transform::TransformDirection(const glm::quat & _orientation)
{
	return WorldOrientation() * _orientation;
}

glm::vec3 Transform::TransformDirection(const glm::vec3 & _direction)
{
	return glm::eulerAngles(
		TransformDirection(
			glm::quat_cast(glm::eulerAngleXYZ(_direction.x, _direction.y, _direction.z))));
}

glm::vec3 Transform::TransformScalar(const glm::vec3 & _scalar)
{
	return WorldScale() * _scalar;
}

glm::vec4 Transform::InverseTransformPoint(const glm::vec4 & _point)
{
	return LocalMatrix() * (InverseWorldMatrix() *  _point);
}

glm::vec3 Transform::InverseTransformPoint(const glm::vec3 & _point)
{
	return glm::vec3(InverseTransformPoint(glm::vec4(_point, 1)));
}

glm::quat Transform::InverseTransformDirection(const glm::quat & _orientation)
{
	return LocalOrientation() * (glm::conjugate(WorldOrientation()) *  _orientation);
}

glm::vec3 Transform::InverseTransformDirection(const glm::vec3 & _direction)
{
	return glm::eulerAngles(
		InverseTransformDirection(
			glm::quat_cast(glm::eulerAngleXYZ(_direction.x, _direction.y, _direction.z))));
}

glm::vec4 Transform::InverseTransformVector(const glm::vec4 & _vector)
{
	return LocalMatrix() * (InverseWorldMatrix() *  _vector);
}

glm::vec3 Transform::InverseTransformVector(const glm::vec3 & _vector)
{
	return glm::vec3(InverseTransformVector(glm::vec4(_vector, 1)));
}

glm::vec3 Transform::InverseTransformScalar(const glm::vec3 & _scalar)
{
	return _scalar / WorldScale();
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
	return glm::normalize(TransformVector(Vector3::forward));
}

const glm::quat & Transform::LocalOrientation()
{
	return m_orientationLocal;
}

glm::vec3 Transform::WorldPosition()
{
	const glm::mat4& mat = WorldMatrix();
	return glm::vec3(mat[0][3], mat[1][3], mat[2][3]);
}

glm::quat Transform::WorldOrientation()
{
	return isRoot() ? m_orientationLocal : parent->WorldOrientation() * m_orientationLocal;
}

glm::vec3 Transform::WorldRotation()
{
	return glm::vec3();
}

glm::vec3 Transform::WorldScale()
{
	return glm::vec3();
}
