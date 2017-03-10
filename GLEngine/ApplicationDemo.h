#pragma once

class CameraBase;
class Camera;

class Shader;
class RenderData;
class Texture;
class Material;
class Transform;
class RenderableObject;
class Light;

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
	Camera* m_camera;

	Shader* m_primativeShader;
	Shader* m_basicObjShader;
	Shader* m_tintTexObjShader;
	Shader* m_texObjShader;

	Texture* m_signDiffuse;

	Texture* m_texSpearDiffuse;
	Texture* m_texSpearSpecular;
	Texture* m_texSpearNormal;

	RenderData* m_groundRenderData;
	RenderData* m_signRenderData;
	std::vector<RenderData*> m_spearRenderData;

	Material* m_groundMat;
	Material* m_signMat;
	Material* m_spearMat;

	RenderableObject* m_ground;
	RenderableObject* m_sign;
	RenderableObject* m_spear;

	Light* m_lightAlpha;
};
