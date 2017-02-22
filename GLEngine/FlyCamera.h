#pragma once
#include "CameraBase.h"

struct GLFWwindow;

class FlyCamera : public CameraBase
{
public:
	FlyCamera(GLFWwindow* _window, float _speed);
	~FlyCamera();

	void Update(float _deltaTime);

	void SetSpeed(float _newSpeed);
	float GetSpeed() const;

private:
	GLFWwindow* m_window;
	float m_speed;
};
