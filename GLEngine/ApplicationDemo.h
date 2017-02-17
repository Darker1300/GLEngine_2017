#pragma once

class ShaderProgram;
class Camera;
class Mesh;

#include "ApplicationBase.h"

class ApplicationDemo : public ApplicationBase
{
public:
	ApplicationDemo();
	~ApplicationDemo();

	virtual int Start();
	virtual int Shutdown();
	virtual int Update(double _deltaTime);
	virtual int Draw();

protected:
	ShaderProgram* m_shaderProgram;
	Camera* m_camera;
	Mesh* m_quad;
	Mesh* m_sphere;
	int _bounceDir;
};
