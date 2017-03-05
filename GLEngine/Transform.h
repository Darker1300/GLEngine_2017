#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <list>

namespace Vector3 {
	// 0, 0, -1
	extern const glm::vec3 backward;
	// 0, -1, 0
	extern const glm::vec3 down;
	// 0, 0, 1
	extern const glm::vec3 forward;
	// -1, 0, 0
	extern const glm::vec3 left;
	// 1, 1, 1
	extern const glm::vec3 one;
	// 1, 0, 0
	extern const glm::vec3 right;
	// 0, 1, 0
	extern const glm::vec3 up;
	// 0, 0, 0
	extern const glm::vec3 zero;
}

class Transform
{
public:
	Transform();

	// TODO COPY/MOVE

	~Transform();

	// ------- Getters ------
#pragma region Getters
	/// <summary><para>Get cached local-space Translation Vector3.</para></summary>
	const glm::vec3& LocalPosition();
	/// <summary><para>Get cached local-space Scale Vector3.</para></summary>
	const glm::vec3& LocalScale();
	/// <summary><para>Get valid cached world-space transformation matrix.</para></summary>
	const glm::quat& LocalOrientation();
	/// <summary><para>Get valid cached local-space transformation matrix.</para></summary>
	const glm::mat4& LocalMatrix();
	/// <summary><para>Get valid cached world-space transformation matrix.</para></summary>
	const glm::mat4& WorldMatrix();
	/// <summary><para>Get valid cached inverse of WorldMatrix (which is a world-space transformation matrix).</para></summary>
	const glm::mat4& InverseMatrix();
	/// <summary><para>Get valid cached world-space orientation in quaternion-form.</para></summary>
	const glm::quat& WorldOrientation();

	/// <summary><para>Calculate world-space Translation Vector3.</para></summary>
	glm::vec3 WorldPosition();
	/// <summary><para>Calculate world-space Scale Vector3. Does not use matrices.</para></summary>
	glm::vec3 WorldScale();

	/// <summary><para>Transforms _point from local space to world space. This is affected by translation, rotation and scale.</para></summary>
	glm::vec3 TransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from local space to world space. This is affected by rotation and scale.</para></summary>
	glm::vec3 TransformVector(const glm::vec3 & _vector);
	/// <summary><para>Transforms _direction from local space to world space. This is affected by rotation.</para></summary>
	glm::vec3 TransformDirection(const glm::vec3 & _direction);
	/// <summary><para>Transforms _point from world space to local space. This is affected by translation, rotation and scale.</para></summary>
	glm::vec3 InverseTransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from world space to local space. This is affected by rotation and scale.</para></summary>
	glm::vec3 InverseTransformVector(const glm::vec3 & _vector);
	/// <summary><para>Transforms _direction from world space to local space. This is affected by rotation.</para></summary>
	glm::vec3 InverseTransformDirection(const glm::vec3 & _direction);

	/// <summary><para>Returns an Unit vector of 'local-space Up direction' transformed into world space.</para></summary>
	glm::vec3 Up();
	/// <summary><para>Returns an Unit vector of 'local-space Right direction' transformed into world space.</para></summary>
	glm::vec3 Right();
	/// <summary><para>Returns an Unit vector of 'local-space Forward direction' transformed into world space.</para></summary>
	glm::vec3 Forward();

	// --------- Hierarchy ---------
	/// <summary><para>Is this transform at the top of hierarchy.</para></summary>
	bool isRoot() const;
	/// <summary><para>Answers the age-old question of 'Is this child mine?'.</para></summary>
	bool isChildOf(const Transform* const _parent) const;
	/// <summary><para>Fills _outContainer with the the children of this instance.</para></summary>
	void GetChildren(std::list<Transform*>& _outContainer);
	/// <summary><para>Fills _outCount with the number of children of this instance.</para></summary>
	void GetChildrenCount(unsigned int& _outCount);
	/// <summary><para>Fills _outContainer with the children hierarchy beneath, including this instance first.</para>
	/// <para>Ordered Depth-First.</para></summary>
	void GetHierarchy(std::list<Transform*>& _outContainer);
	/// <summary><para>Fills _outCount with the number of transforms in the children hierarchy beneath, including this instance.</para></summary>
	void GetHierarchyCount(unsigned int& _outCount);
#pragma endregion Getters

#pragma region Setters
	// ------- Transformation ------
	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Translate(const glm::vec3 & _vector);
	void Rotate(const glm::quat & _rot);
	/// <summary><para>Apply local rotation. _rot are euler radians. Order: Z, X, Y.</para></summary>
	void Rotate(const glm::vec3 & _rot);
	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Scale(const glm::vec3 & _scalar);
	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Scale(const float & _scalar);
	// --------- Hierarchy ---------
	void SetParent(Transform* _parent, bool _maintainTransform = true);
	void DetachChildren();
#pragma endregion Setters

private:
	// --------- Variables ---------
	// Basic Components
	glm::vec3 position;
	glm::quat orientation;
	glm::vec3 scale;
	// Transformation Matrices
	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 worldInverseMatrix;
	// Orientation Quaternions
	glm::quat worldOrientation;
	// Flags
	bool invalidLocal;
	bool invalidWorld;
	bool invalidWorldInverse;
	bool invalidWorldOrientation;
	// Hierarchy
	Transform* parent;
	std::list<Transform*> children;

	// ----- Helper functions ------
	// Validate Helpers
	void ValidateLocal();
	void ValidateWorld();
	void ValidateWorldInverse();
	void ValidateWorldOrientation();
	// Invalidate Helpers
	void InvalidateLocal();
	void InvalidateWorld();
	void InvalidateWorldOrientation();
	void InvalidateChildren();
	// Calculate Helpers
	void CalculateLocal();
	void CalculateWorld();
	void CalculateWorldInverse();
	void CalculateWorldOrientation();

	void ClampRadians(const glm::vec3& _source, glm::vec3& _output) const;
};
