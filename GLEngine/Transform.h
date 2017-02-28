#pragma once
#include <glm\glm.hpp>
#include <glm/glm/gtx/quaternion.hpp>
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

/// <summary>
///<para>This is used to store and manipulate the position, rotation and scale of the object.</para>
///<para>Every Transform can have a parent, which allows you to apply position, rotation and scale hierarchically.</para>
///</summary>.
class Transform
{
public:
	// -------- Constructors -------
#pragma region Constructors
	/// <summary><para>Default Constructor</para></summary>
	Transform();
	/// <summary><para>Copy Constructor</para></summary>
	Transform(const Transform& _other);
	/// <summary><para>Move Constructor</para></summary>
	Transform(Transform&& _other);

	/// <summary><para>Destructor</para></summary>
	~Transform();
	// -----------------------------

	// --------- Operators ---------
	/// <summary><para>Copy operator</para></summary>
	Transform& operator=(const Transform& _other);
	/// <summary><para>Move operator</para></summary>
	Transform& operator=(Transform&& _other);
#pragma endregion Constructors
	// -----------------------------

	// ------- Transformation ------
#pragma region Transformation
	/// <summary><para>Transforms _point from local space to world space. This is affected by scale.</para></summary>
	glm::vec4 TransformPoint(const glm::vec4 & _point);
	/// <summary><para>Transforms _point from local space to world space. This is affected by scale.</para></summary>
	glm::vec3 TransformPoint(const glm::vec3 & _point);

	/// <summary><para>Transforms _vector from local space to world space.</para></summary>
	glm::vec4 TransformVector(const glm::vec4 & _vector);
	/// <summary><para>Transforms _vector from local space to world space.</para></summary>
	glm::vec3 TransformVector(const glm::vec3 & _vector);

	/// <summary><para>Transforms _orientation from local space to world space.</para></summary>
	glm::quat TransformDirection(const glm::quat & _orientation);
	/// <summary><para>Transforms _direction from local space to world space.</para></summary>
	glm::vec3 TransformDirection(const glm::vec3 & _direction);

	/// <summary><para>Transforms _scalar from local space to world space.</para></summary>
	glm::vec3 TransformScalar(const glm::vec3 & _scalar);

	/// <summary><para>Transforms _point from world space to local space. This is affected by scale.</para></summary>
	glm::vec4 InverseTransformPoint(const glm::vec4 & _point);
	/// <summary><para>Transforms _point from world space to local space. This is affected by scale.</para></summary>
	glm::vec3 InverseTransformPoint(const glm::vec3 & _point);

	/// <summary><para>Transforms Quaternion _orientation from world space to local space.</para></summary>
	glm::quat InverseTransformDirection(const glm::quat & _orientation);
	/// <summary><para>Transforms Euler Angles _direction from world space to local space.</para></summary>
	glm::vec3 InverseTransformDirection(const glm::vec3 & _direction);

	/// <summary><para>Transforms _vector from world space to local space. This is unaffected by scale.</para></summary>
	glm::vec4 InverseTransformVector(const glm::vec4 & _vector);
	/// <summary><para>Transforms _vector from world space to local space. This is unaffected by scale.</para></summary>
	glm::vec3 InverseTransformVector(const glm::vec3 & _vector);

	/// <summary><para>Transforms _scalar from world space to local space.</para></summary>
	glm::vec3 InverseTransformScalar(const glm::vec3 & _scalar);

	/// <summary><para>Returns an Unit vector of 'local-space Up direction' transformed into world space.</para></summary>
	glm::vec3 Up();
	/// <summary><para>Returns an Unit vector of 'local-space Right direction' transformed into world space.</para></summary>
	glm::vec3 Right();
	/// <summary><para>Returns an Unit vector of 'local-space Forwards direction' transformed into world space.</para></summary>
	glm::vec3 Forwards();

#pragma endregion Transformation
	// -----------------------------

	// --------- Hierarchy ---------
#pragma region Hierarchy
	void SetParent(Transform* _parent);

	bool isRoot() const;
	bool isChildOf(Transform* _parent);

	/// <summary><para>Adds _child to this instance's hierarchy.</para></summary>
	void AddChild(Transform* _child);

	/// <summary><para>Removes _child from this instance's children.</para></summary>
	void RemoveChild(Transform* _child);
	/// <summary><para>Removes _child from this instance's hierarchy.</para></summary>
	bool RemoveChildFromChildren(Transform* _child);

	/// <summary><para>Returns the top-most parent of this instance.</para></summary>
	Transform* GetRoot();
	/// <summary><para>Returns a collection of child transforms for this instance.</para></summary>
	void GetChildren(std::list<Transform*>& _outContainer);
	/// <summary><para>Fills _outContainer with the children hierarchy beneath, including this instance first.</para>
	/// <para>Ordered Depth-First.</para></summary>
	void GetHierarchy(std::list<Transform*>& _outContainer);
	/// <summary><para>Fills _outCount with the number of transforms in the children hierarchy beneath, including this instance.</para></summary>
	void GetHierarchyCount(unsigned int& _outCount);
#pragma endregion Hierarchy
	// -----------------------------
	
	// ---------- Getters ----------
#pragma region Getters
	// Local
	/// <summary><para>Get Local Translation Vector3. This is cached.</para></summary>
	const glm::vec3& LocalPosition();
	/// <summary><para>Get Local Scale Vector3. This is cached.</para></summary>
	const glm::vec3& LocalScale();

	/// <summary><para>Get Local Orientation quaternion. This is cached.</para></summary>
	const glm::quat& LocalOrientation();
	/// <summary><para>Calculate Local Rotation Euler Angles.</para></summary>
	glm::vec3 LocalRotation();

	/// <summary><para>Get Local Translation Matrix.</para></summary>
	glm::mat4 LocalTranslateMatrix();
	/// <summary><para>Calculate Local Scale Matrix.</para></summary>
	glm::mat4 LocalScaleMatrix();
	/// <summary><para>Calculate Local Rotation Matrix.</para></summary>
	glm::mat4 LocalRotationMatrix();
	/// <summary><para>Get Local Transformation Matrix. This is cached.</para></summary>
	const glm::mat4& LocalMatrix();

	// World
	/// <summary><para>Calculate World Translation Vector3.</para></summary>
	glm::vec3 WorldPosition();
	/// <summary><para>Calculate World Orientation Quaternion.</para></summary>B
	glm::quat WorldOrientation();
	/// <summary><para>Calculate World Rotation Euler Angles.</para></summary>B
	glm::vec3 WorldRotation();
	/// <summary><para>Calculate World Scale Vector3.</para></summary>
	glm::vec3 WorldScale();

	/// <summary><para>Get World Transformation Matrix. This is cached.</para></summary>
	const glm::mat4& WorldMatrix();
	/// <summary><para>Get Inverse World Transformation Matrix. This is cached.</para></summary>
	const glm::mat4& InverseWorldMatrix();
#pragma endregion Getters
	// -----------------------------

	// ---------- Setters ----------
#pragma region Setters
	// Local
	/// <summary><para>Set Local Translation Vector3.</para></summary>
	void SetLocalPosition(const glm::vec3& _pos);

	/// <summary><para>Set Local Orientation quaternion.</para></summary>
	void SetLocalOrientation(const glm::quat& _quat);
	/// <summary><para>Set Local Rotation Euler Angles.</para></summary>
	void SetLocalRotation(const glm::vec3& _rot);

	/// <summary><para>Set Local Scale Vector3.</para></summary>
	void SetLocalScale(const glm::vec3& _scale);

	// World
	/// <summary><para>Set World Translation Vector3.</para></summary>
	void SetWorldPosition(const glm::vec3& _pos);

	/// <summary><para>Set World Orientation quaternion.</para></summary>
	void SetWorldOrientation(const glm::quat& _quat);
	/// <summary><para>Set World Rotation Euler Angles.</para></summary>
	void SetWorldRotation(const glm::vec3& _rot);

	/// <summary><para>Set World Scale Vector3.</para></summary>
	void SetWorldScale(const glm::vec3& _scale);
#pragma endregion Setters
	// -----------------------------

private:
#pragma region Helpers
	// -------- Flag Helpers --------
#pragma region Flag Helpers
	//void InvalidateTranslationMatrix();
	//void InvalidateRotationMatrix();
	//void InvalidateScaleMatrix();
	void InvalidateLocalMatrix();
	void InvalidateWorldMatrix();
	void InvalidateInverseWorldMatrix();
#pragma endregion Flag Helpers
	// -----------------------------

	// ---- Calculation Helpers ----
#pragma region Calculation Helpers
	/*struct Math {
		static void Convert(const glm::vec3& _eulers, glm::quat& _outQuat);
		static void Convert(const glm::quat& _quat, glm::vec3& _outEulers);
	};*/
	//void CalcTranslationMatrix();
	//void CalcScaleMatrix();
	//void CalculateRotationMatrix();
	//void CalculateLocalTransform();
	//void CalculateWorldTransform();
	//void CalculateInverseWorldTransform();
#pragma endregion Calculation Helpers
	// -----------------------------

	// Rotation Conversion Functions
	//struct Math {
	//	static void CalculateRotation(const glm::vec3& _eulers, glm::quat& _outQuat);
	//	static void CalculateRotation(const glm::quat& _quat, glm::vec3& _outEulers);
	//	static void CalculateRotation(const glm::vec3& _eulers, glm::mat4& _outMat4);
	//	static void CalculateRotation(const glm::quat& _quat, glm::mat4& _outMat4);
	//	static void CalculateRotation(const glm::mat4& _mat4, glm::quat& _outQuat);
	//};
	// -----------------------------

#pragma endregion Helpers

	// --------- Variables ---------
#pragma region Variables
	glm::vec3 m_positionLocal;
	glm::quat m_orientationLocal;
	glm::vec3 m_scaleLocal;

	glm::mat4 m_transformLocalMatrix;
	glm::mat4 m_transformWorldMatrix;
	glm::mat4 m_transformInverseWorldMatrix;

	Transform* parent;
	std::list<Transform*> children;

	// ----------- Flags -----------
#pragma region Flags
	bool m_changedLocalTransform;
	bool m_changedWorldTransform;
	bool m_changedInverseWorldTransform;
#pragma endregion Flags

#pragma endregion Variables
	// -----------------------------
};
