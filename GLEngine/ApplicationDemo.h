#pragma once

class ShaderProgram;
class Camera;
class Model;

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
	Model* m_quad;
	Model* m_sphere;
	int _bounceDir;
};
