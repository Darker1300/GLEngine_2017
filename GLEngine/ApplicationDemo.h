#pragma once

class ShaderProgram;
class CameraBase;
class Mesh;
namespace gl { class Texture; };

class Shader;
class RenderData;
class Transform;

#include "ApplicationBase.h"
#include <vector>

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
	Shader* m_planeShader;
	RenderData* m_planeRenderData;

	Shader* m_ianShader;
	RenderData* m_ianRenderData;
	Transform* m_ianTransform;

	Shader* m_objShader;
	std::vector<RenderData*> m_dragonRenderData;
	Transform* m_dragonTransform;

	ShaderProgram* m_shaderProgram;
	CameraBase* m_camera;
	Mesh* m_quad;
	Mesh* m_sphere;
	gl::Texture* m_texTest;
	gl::Texture* m_texIan;
};
