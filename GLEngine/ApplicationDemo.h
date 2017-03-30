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
class RenderTarget;

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
	Shader* m_basicShader;
	Shader* m_tintTexShader;
	Shader* m_phongShader;
	Shader* m_depthTargetShader;

	Texture* m_texWhite;

	Texture* m_texSignDiffuse;

	Texture* m_texSpearDiffuse;
	Texture* m_texSpearSpecular;
	Texture* m_texSpearNormal;

	RenderTarget* m_renderTarget1;

	RenderData* m_groundRenderData;
	RenderData* m_signRenderData;
	std::vector<RenderData*> m_spearRenderData;
	RenderData* m_mirrorRenderData;
	RenderData* m_screenRenderData;

	Material* m_groundMat;
	Material* m_signMat;
	Material* m_spearMat;
	Material* m_mirrorMat;

	RenderableObject* m_ground;
	RenderableObject* m_sign;
	RenderableObject* m_spear;
	RenderableObject* m_mirror;

	Light* m_lightAlpha;
};
