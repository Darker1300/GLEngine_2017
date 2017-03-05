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

	const glm::vec3& GetScale() const { return m_scale; }
	inline const float& GetYaw() const { return m_rotation[0]; }
	inline const float& GetPitch() const { return m_rotation[1]; }
	inline const float& GetRoll() const { return m_rotation[2]; }
	const glm::vec3& GetPosition() const { return m_position; }

	glm::mat4 GetLocalMatrix();
	glm::mat4 GetRotationMatrix();

	void SetRotation(const glm::vec3& _rotation) { SetYaw(_rotation[0]); SetPitch(_rotation[1]); SetRoll(_rotation[2]); };
	void AddRotation(const glm::vec3& _rotation) { SetRotation(m_rotation + _rotation); };
	inline void SetYaw(float _radians) { m_rotation[0] = fmodf(_radians, glm::two_pi<float>()); }
	inline void SetPitch(float radians) { m_rotation[1] = fmodf(radians, glm::two_pi<float>()); }
	inline void SetRoll(float radians) { m_rotation[2] = fmodf(radians, glm::two_pi<float>()); }

	inline void AddYaw(float _radians) { SetYaw(GetYaw() + _radians); }
	inline void AddPitch(float _radians) { SetPitch(GetPitch() + _radians); }
	inline void AddRoll(float _radians) { SetRoll(GetRoll() + _radians); }

	glm::vec3 m_scale;
	// Pitch, Yaw, Roll
	glm::vec3 m_rotation;
	glm::vec3 m_position;
};
