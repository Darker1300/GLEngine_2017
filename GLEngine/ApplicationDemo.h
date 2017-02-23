#pragma once

class ShaderProgram;
class CameraBase;
class Mesh;
namespace gl { class Texture; };

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
	gl::Texture* m_tex;
	//int _bounceDir;
};
