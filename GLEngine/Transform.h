#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <list>

namespace Vector3 {
	// 0, 0, -1
	extern const glm::vec3 backward;
	// 0, 0, 1
	extern const glm::vec3 forward;
	// 0, 1, 0
	extern const glm::vec3 up;
	// 0, -1, 0
	extern const glm::vec3 down;
	// 1, 0, 0
	extern const glm::vec3 right;
	// -1, 0, 0
	extern const glm::vec3 left;
	// 1, 1, 1
	extern const glm::vec3 one;
	// 0, 0, 0
	extern const glm::vec3 zero;
}

class Transform
{
public:
	Transform();
	~Transform();

	//const glm::vec3& GetScale() const { return scale; }
	//inline const float& GetPitch() const { return pitch; }
	//inline const float& GetYaw() const { return yaw; }
	//inline const float& GetRoll() const { return roll; }
	//const glm::vec3& GetPosition() const { return position; }

	glm::mat4 GetRotationMatrix();
	glm::mat4 GetLocalMatrix();

	void SetRotation(const glm::vec3& _rotation) { SetRoll(_rotation[2]); SetYaw(_rotation[0]); SetPitch(_rotation[1]); };
	void AddRotation(const glm::vec3& _rotation) { SetRotation(forward + _rotation); };
	inline void SetPitch(float _radians) { pitch = ClampRadian(_radians); }
	inline void SetYaw(float _radians) { yaw = ClampRadian(_radians); }
	inline void SetRoll(float _radians) { roll = ClampRadian(_radians); }

	inline void AddPitch(float _radians) { SetPitch(pitch + _radians); }
	inline void AddYaw(float _radians) { SetYaw(yaw + _radians); }
	inline void AddRoll(float _radians) { SetRoll(roll + _radians); }

	inline static float ClampRadian(const float& _value) { return fmodf(_value, glm::two_pi<float>()); }

	glm::vec3 scale;
	union {
		glm::vec3 forward;
		struct { float yaw, pitch, roll; };
	};
	glm::vec3 position;
};
