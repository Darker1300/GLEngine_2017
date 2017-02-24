#pragma once
#include <glm\glm.hpp>

namespace Vector3 {
	static const glm::vec3 up = glm::vec3(0, 1, 0);
	static const glm::vec3 right = glm::vec3(1, 0, 0);
	static const glm::vec3 forward = glm::vec3(0, 0, 1);
}

class Transform
{
public:
	Transform();
	~Transform();

	void Invalidate();

	glm::vec3 TransformPoint(const glm::vec3 & _point);
	glm::vec3 TransformVector(const glm::vec3 & _vector);

	glm::vec3 Up();
	glm::vec3 Right();
	glm::vec3 Forwards();

	glm::mat4& RotMatrix();
	glm::mat4& WorldMatrix();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

private:
	glm::mat4 rotMatrix;
	glm::mat4 worldMatrix;
	bool m_changed;

	void UpdateMatrices();
	void RecalcMatrices();
	void RecalcRotation();
};

