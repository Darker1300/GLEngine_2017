#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Transform.h"

#include <glm\gtx\transform.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm\ext.hpp>

static const glm::vec3 Vector3::backward = glm::vec3(0, 0, -1);
static const glm::vec3 Vector3::down = glm::vec3(0, -1, 0);
static const glm::vec3 Vector3::forward = glm::vec3(0, 0, 1);
static const glm::vec3 Vector3::left = glm::vec3(-1, 0, 0);
static const glm::vec3 Vector3::one = glm::vec3(1, 1, 1);
static const glm::vec3 Vector3::right = glm::vec3(1, 0, 0);
static const glm::vec3 Vector3::up = glm::vec3(0, 1, 0);
static const glm::vec3 Vector3::zero = glm::vec3(0, 0, 0);

Transform::Transform()
	: m_scale(1), m_rotation(), m_position()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetLocalMatrix()
{
	// scale
	glm::mat4 local = glm::mat4();
	local = glm::scale(local, m_scale);
	// rotate
	local = GetRotationMatrix() * local;
	// translate
	local = glm::translate(local, m_position);
	return local;
}

glm::mat4 Transform::GetRotationMatrix()
{
	// rotate around to yaw
	glm::mat4 rotation = glm::rotate(glm::mat4(), GetYaw(), Vector3::up);
	// rotate around to pitch
	rotation = glm::rotate(rotation, GetPitch(), Vector3::right);
	// rotate around to roll
	rotation = glm::rotate(rotation, GetRoll(), Vector3::forward);

	return rotation;
}
