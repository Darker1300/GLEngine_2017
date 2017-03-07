#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "ApplicationDemo.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "ShaderProgram.h"
#include "ShaderCollection.h"
#include "Mesh.h"
#include "Primatives.h"
#include "Texture.h"

#include "Shader.h"
#include "RenderData.h"
#include "GeometryHelper.h"
#include "Transform.h"
#include "Material.h"
#include "RenderableObject.h"
#include "Camera.h"

ApplicationDemo::ApplicationDemo()
	: ApplicationBase("Game Engine Demo", 1280, 720) {}

ApplicationDemo::~ApplicationDemo() {}

int ApplicationDemo::Start()
{
	if (ApplicationBase::Start()) return -1;

	// Set Background color
	SetBackgroundColor(0.25f, 0.25f, 0.25f);

	// Set DrawMode:
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Turn on Wireframe:
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Set up Camera
	m_camera = new Camera();
	m_camera->position += Vector3::up * 0.5f;
	m_camera->position += Vector3::backward * 4;
	 m_camera->yaw += glm::radians(180.0f);

	// Shaders
	m_primativeShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
	m_basicObjShader = new Shader("./shaders/basicOBJ.vert", "./shaders/basicOBJ.frag");
	m_texturedObjShader = new Shader("./shaders/ian.vert", "./shaders/ian.frag");

	// Textures
	m_signDiffuse = new Texture("./textures/ian.png");
	m_texSpearDiffuse = new Texture("./models/soulspear/soulspear_diffuse.tga");

	// RenderData
	m_groundRenderData = GeometryHelper::CreatePlane(10, 10, 10, 10, { 0.0f, 0.4f, 0.0f, 1 });
	m_signRenderData = GeometryHelper::CreatePlane(2, 2, 4, 2, { 0, 0.5f, 1, 1 });
	m_spearRenderData = GeometryHelper::LoadOBJFromDisk("./models/soulspear/soulspear.obj"); //stanford/dragon

	// Materials
	m_groundMat = new Material(m_primativeShader);
	m_spearMat = new Material(m_texturedObjShader);
	m_signMat = new Material(m_texturedObjShader);

	// Set Textures
	m_signMat->m_textures["diffuse"] = m_signDiffuse;
	m_spearMat->m_textures["diffuse"] = m_texSpearDiffuse;

	// RenderableObjects
	m_ground = new RenderableObject(m_groundMat, std::vector<RenderData*>{ m_groundRenderData });
	m_sign = new RenderableObject(m_signMat, std::vector<RenderData*>{ m_signRenderData });
	m_spear = new RenderableObject(m_spearMat, m_spearRenderData);

	// Set Transforms
	m_spear->m_transform.scale = Vector3::one;
	m_spear->m_transform.position += Vector3::up * 0.25f;

	//		m_sign->m_transform.SetParent(&m_spear->m_transform);	
	// m_sign->m_transform.SetPitch(glm::radians(90.0f));
	m_sign->m_transform.position += Vector3::backward * 10.0f;
	m_sign->m_transform.position += Vector3::left / 8.0f;

	return 0;
}

int ApplicationDemo::Shutdown()
{
	if (ApplicationBase::Shutdown()) return -1;

	delete m_spear;
	delete m_sign;
	delete m_ground;

	delete m_spearMat;
	delete m_signMat;
	delete m_groundMat;

	for (auto data : m_spearRenderData) delete data;
	delete m_signRenderData;
	delete m_groundRenderData;

	delete m_texSpearDiffuse;
	delete m_signDiffuse;

	delete m_texturedObjShader;
	delete m_basicObjShader;
	delete m_primativeShader;

	delete m_camera;
	return 0;
}

int ApplicationDemo::FixedUpdate(double _deltaTime)
{
	if (ApplicationBase::FixedUpdate(_deltaTime)) return -1;
	//m_signTransform->Rotate({ 0,1 * _deltaTime,0 });
	return 0;
}

int ApplicationDemo::Update(double _deltaTime)
{
	if (ApplicationBase::Update(_deltaTime)) return -1;

	// Camera controls
	m_camera->UpdateFly(GetWindow(), (float)_deltaTime, 4);
	// m_camera->Update((float)_deltaTime);

	// Transformations
	//m_spear->m_transform.Rotate(m_spear->m_transform.Up() * _deltaTime * 0.5f);
	// m_sign->m_transform.Translate({});

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	glm::mat4 projView = m_camera->GetProjectionViewMatrix();

	// Update material
	m_ground->Bind();
	m_groundMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_groundMat->ApplyUniformMat4("modelMatrix", m_ground->m_transform.GetLocalMatrix());
	// Render
	m_ground->Render();
	m_ground->Unbind();


	// Update material
	m_sign->Bind();
	m_signMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_signMat->ApplyUniformMat4("modelMatrix", m_sign->m_transform.GetLocalMatrix());
	// Render
	m_sign->Render();
	m_sign->Unbind();


	// Update material
	m_spear->Bind();
	m_spearMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_spearMat->ApplyUniformMat4("modelMatrix", m_spear->m_transform.GetLocalMatrix());
	// Render
	m_spear->Render();
	m_spear->Unbind();

	//// Plane
	//glUseProgram(m_primativeShader->GetProgramID());
	//// Set Uniform
	//int PVMatLoc1 = glGetUniformLocation(m_primativeShader->GetProgramID(), "projectionViewMatrix");
	//glUniformMatrix4fv(PVMatLoc1, 1, false, glm::value_ptr(projView));

	//m_groundRenderData->Render();

	//// OBJ
	//glUseProgram(m_basicObjShader->GetProgramID());
	//// Set Uniform
	//int PVMatLoc2 = glGetUniformLocation(m_basicObjShader->GetProgramID(), "projectionViewMatrix");
	//glUniformMatrix4fv(PVMatLoc2, 1, false, glm::value_ptr(projView));
	//int modelMatLoc2 = glGetUniformLocation(m_basicObjShader->GetProgramID(), "modelMatrix");
	//glUniformMatrix4fv(modelMatLoc2, 1, false, glm::value_ptr(m_dragonTransform->WorldMatrix()));

	//for (RenderData*& data : m_spearRenderData)
	//	data->Render();

	//// Ian
	//glUseProgram(m_texturedObjShader->GetProgramID());

	//// set texture slot
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_signDiffuse->GetID());
	//// tell the shader where it is 
	//unsigned int texLoc1 = glGetUniformLocation(m_texturedObjShader->GetProgramID(), "diffuse");
	//if (texLoc1 < 0) { LOG_ERROR("glGetUniformLocation( diffuse ) failed.") }
	//glUniform1i(texLoc1, 0);

	//int PVMatLoc3 = glGetUniformLocation(m_texturedObjShader->GetProgramID(), "projectionViewMatrix");
	//glUniformMatrix4fv(PVMatLoc3, 1, false, glm::value_ptr(projView));
	//int modelMatLoc3 = glGetUniformLocation(m_texturedObjShader->GetProgramID(), "modelMatrix");
	//glUniformMatrix4fv(modelMatLoc3, 1, false, glm::value_ptr(m_signTransform->WorldMatrix()));

	//m_signRenderData->Render();

	//// Spear
	//glBindTexture(GL_TEXTURE_2D, m_texSpearDiffuse->GetID());
	//// glUniform1i() 0 is for GL_TEXTURE0. 1 is for GL_TEXTURE1
	//glUniform1i(texLoc1, 0);

	//glUseProgram(0);

	return 0;
}

