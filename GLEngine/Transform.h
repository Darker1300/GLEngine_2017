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
	~Transform();

	// ------- Getters ------
#pragma region Getters
	/// <summary><para>Get cached local-space Translation Vector3.</para></summary>
	const glm::vec3& LocalPosition();
	/// <summary><para>Get cached local-space Scale Vector3.</para></summary>
	const glm::vec3& LocalScale();
	// /// <summary><para>Get cached local-space Euler rotation in radians.</para></summary>
	//const glm::vec3& LocalRotation();
	const glm::quat& LocalOrientation();
	/// <summary><para>Get valid cached local-space rotation matrix.</para></summary>
	const glm::mat4& RotMatrix();
	/// <summary><para>Get valid cached local-space transformation matrix.</para></summary>
	const glm::mat4& LocalMatrix();
	/// <summary><para>Get valid cached world-space transformation matrix.</para></summary>
	const glm::mat4& WorldMatrix();
	/// <summary><para>Get valid cached inverse of WorldMatrix (which is a world-space transformation matrix).</para></summary>
	const glm::mat4& InverseMatrix();

	/// <summary><para>Calculate world-space Translation Vector3.</para></summary>
	glm::vec3 WorldPosition();
	// /// <summary><para>Calculate world-space Euler rotation in radians.</para></summary>
	//glm::vec3 WorldRotation();
	/// <summary><para>Calculate world-space Scale Vector3. Does not use matrices.</para></summary>
	glm::vec3 WorldScale();

	/// <summary><para>Transforms _point from local space to world space. This is affected by scale.</para></summary>
	glm::vec3 TransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from local space to world space. This is unaffected by scale.</para></summary>
	glm::vec3 TransformVector(const glm::vec3 & _vector);
	/// <summary><para>Transforms _point from world space to local space. This is affected by scale.</para></summary>
	glm::vec3 InverseTransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from world space to local space. This is unaffected by scale.</para></summary>
	glm::vec3 InverseTransformVector(const glm::vec3 & _vector);

	/// <summary><para>Returns an Unit vector of 'local-space Up direction' transformed into world space.</para></summary>
	glm::vec3 Up();
	/// <summary><para>Returns an Unit vector of 'local-space Right direction' transformed into world space.</para></summary>
	glm::vec3 Right();
	/// <summary><para>Returns an Unit vector of 'local-space Forward direction' transformed into world space.</para></summary>
	glm::vec3 Forward();

	/// <summary><para>Returns an euler rotation vector of 'local-space Up direction', decomposed from local rotation matrix.</para></summary>
	glm::vec3 UpLocalAxis();
	/// <summary><para>Returns an euler rotation vector of 'local-space Right direction', decomposed from local rotation matrix.</para></summary>
	glm::vec3 RightLocalAxis();
	/// <summary><para>Returns an euler rotation vector of 'local-space Forward direction', decomposed from local rotation matrix.</para></summary>
	glm::vec3 ForwardLocalAxis();

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
	void SetParent(Transform* _parent);
	void DetachChildren();
#pragma endregion Setters

private:
	// --------- Variables ---------
	// Components
	glm::vec3 position;
	//glm::vec3 rotation;
	glm::quat orientation;
	glm::vec3 scale;
	// Matrices
	glm::mat4 rotMatrix;
	glm::mat4 localMatrix;
	glm::mat4 worldMatrix;
	glm::mat4 inverseMatrix;
	// Flags
	bool invalidRotation;
	bool invalidLocal;
	bool invalidWorld;
	bool invalidInverse;
	// Hierarchy
	Transform* parent;
	std::list<Transform*> children;

	// ----- Helper functions ------
	// Validate Helpers
	void ValidateRotation();
	void ValidateLocal();
	void ValidateWorld();
	void ValidateInverse();
	// Calculate Helpers
	void CalculateRotation();
	void CalculateLocal();
	void CalculateWorld();
	void CalculateInverse();

	void ClampRadians(const glm::vec3& _source, glm::vec3& _output) const;
};
