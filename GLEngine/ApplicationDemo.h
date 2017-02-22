#pragma once

class ShaderProgram;
class CameraBase;
class Mesh;

#include "ApplicationBase.h"

class ApplicationDemo : public ApplicationBase
{
public:
	ApplicationDemo();
	~ApplicationDemo();

	int Start();
	int Shutdown();
	int FixedUpdate(double _deltaTime);
	int Update(double _deltaTime);
	int Draw();

protected:
	ShaderProgram* m_shaderProgram;
	CameraBase* m_camera;
	Mesh* m_quad;
	Mesh* m_sphere;
	int _bounceDir;
};
