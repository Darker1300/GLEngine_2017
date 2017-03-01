#pragma once
#include <glm\glm.hpp>
#include <list>

namespace Vector3 {
	extern const glm::vec3 back;
	extern const glm::vec3 down;
	extern const glm::vec3 forward;
	extern const glm::vec3 left;
	extern const glm::vec3 one;
	extern const glm::vec3 right;
	extern const glm::vec3 up;
	extern const glm::vec3 zero;
}

class Transform
{
public:
	Transform();
	~Transform();


	// ------- Transformation ------
#pragma region Transformation
	/// <summary><para>Transforms _point from local space to world space. This is affected by scale.</para></summary>
	glm::vec3 TransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from local space to world space. This is unaffected by scale.</para></summary>
	glm::vec3 TransformVector(const glm::vec3 & _vector);
	/// <summary><para>Transforms _point from world space to local space. This is affected by scale.</para></summary>
	glm::vec3 InverseTransformPoint(const glm::vec3 & _point);
	/// <summary><para>Transforms _vector from world space to local space. This is unaffected by scale.</para></summary>
	glm::vec3 InverseTransformVector(const glm::vec3 & _vector);

	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Translate(const glm::vec3 & _vector);
	/// <summary><para>Apply local rotation. _rot are euler radians.</para></summary>
	void Rotate(const glm::vec3 & _rot);
	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Scale(const glm::vec3 & _scalar);
	/// <summary><para>Apply local translation of _vector.</para></summary>
	void Scale(const float & _scalar);

	glm::vec3 Up();
	glm::vec3 Right();
	glm::vec3 Forwards();

#pragma endregion Transformation

	// ------- Getters ------

	/// <summary><para>Get cached Local Translation Vector3.</para></summary>
	const glm::vec3& LocalPosition();
	/// <summary><para>Get cached Local Scale Vector3.</para></summary>
	const glm::vec3& LocalScale();
	/// <summary><para>Get cached Local Euler Radians Rotation.</para></summary>
	const glm::vec3& LocalRotation();

	/// <summary><para>Get valid cached local-space rotation matrix.</para></summary>
	const glm::mat4& RotMatrix();
	/// <summary><para>Get valid cached local-space transformation matrix.</para></summary>
	const glm::mat4& LocalMatrix();
	/// <summary><para>Get valid cached world-space transformation matrix.</para></summary>
	const glm::mat4& WorldMatrix();
	/// <summary><para>Get valid cached inverse of WorldMatrix.</para></summary>
	const glm::mat4& InverseMatrix();

	bool isRoot() const;

private:
	// --------- Variables ---------
	// Components
	glm::vec3 position;
	glm::vec3 rotation;
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
};

