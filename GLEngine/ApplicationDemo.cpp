#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "ApplicationDemo.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "FlyCamera.h"
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
	//m_camera = new FlyCamera(GetWindow(), 10);
	//m_camera->SetPerspective(
	//	glm::pi<float>() * 0.25f,
	//	(float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight(),
	//	0.1f, 1000.0f);
	m_camera = new Camera();
	m_camera->m_direction = Vector3::forward;
	m_camera->m_position += Vector3::backward * 8;
	m_camera->m_position += Vector3::up * 4;
	m_camera->UpdateView();
	m_camera->SetAsMain();

	// Shaders
	m_primativeShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
	m_basicObjShader = new Shader("./shaders/basicOBJ.vert", "./shaders/basicOBJ.frag");
	m_tintTexObjShader = new Shader("./shaders/ian.vert", "./shaders/ian.frag");
	m_texObjShader = new Shader("./shaders/texOBJ.vert", "./shaders/texOBJ.frag");

	// Textures
	m_signDiffuse = new Texture("./textures/ian.png");
	m_texSpearDiffuse = new Texture("./models/soulspear/soulspear_diffuse.tga");
	m_texSpearSpecular = new Texture("./models/soulspear/soulspear_specular.tga");
	m_texSpearNormal = new Texture("./models/soulspear/soulspear_normal.tga");


	// RenderData
	m_groundRenderData = GeometryHelper::CreatePlane(10, 10, 10, 10, { 0.0f, 0.4f, 0.0f, 1 });
	m_signRenderData = GeometryHelper::CreatePlane(2, 2, 4, 2, { 0, 0.5f, 1, 1 });
	m_spearRenderData = GeometryHelper::LoadOBJFromDisk("./models/soulspear/soulspear.obj"); //stanford/dragon

	// Materials
	m_groundMat = new Material(m_primativeShader);
	m_spearMat = new Material(m_texObjShader);
	m_signMat = new Material(m_tintTexObjShader);

	// Set Textures
	m_signMat->m_textures["diffuse"] = m_signDiffuse;

	m_spearMat->m_textures["normal"] = m_texSpearNormal;
	m_spearMat->m_textures["kD"] = m_texSpearDiffuse;
	m_spearMat->m_textures["kS"] = m_texSpearSpecular;

	// RenderableObjects
	m_ground = new RenderableObject(m_groundMat, std::vector<RenderData*>{ m_groundRenderData });
	m_sign = new RenderableObject(m_signMat, std::vector<RenderData*>{ m_signRenderData });
	m_spear = new RenderableObject(m_spearMat, m_spearRenderData);

	// Set Transforms
	//m_spear->m_transform.Scale(1);//0.01f);
	m_spear->m_transform.Translate(m_spear->m_transform.Up() * 1);

	m_sign->m_transform.SetParent(&m_spear->m_transform);
	//	m_sign->m_transform.Rotate({ 3.14159265f * 0.5f, 0, 0 });
	m_sign->m_transform.Translate(m_sign->m_transform.Up() * 10);

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

	delete m_texSpearNormal;
	delete m_texSpearSpecular;
	delete m_texSpearDiffuse;

	delete m_signDiffuse;

	delete m_texObjShader;
	delete m_tintTexObjShader;
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
	//m_camera->Update((float)_deltaTime);
	m_camera->UpdateFly((float)_deltaTime);
	m_camera->UpdateView();

	// Transformations
	m_spear->m_transform.Rotate(m_spear->m_transform.Up() * _deltaTime * 0.5f);
	// m_sign->m_transform.Translate({});

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	glm::mat4 projView = m_camera->m_projection * m_camera->m_view;

	// Update material
	m_ground->Bind();
	m_groundMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_groundMat->ApplyUniformMat4("modelMatrix", m_ground->m_transform.WorldMatrix());
	// Render
	m_ground->Render();
	m_ground->Unbind();


	// Update material
	m_sign->Bind();
	m_signMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_signMat->ApplyUniformMat4("modelMatrix", m_sign->m_transform.WorldMatrix());
	// Render
	m_sign->Render();
	m_sign->Unbind();


	glm::vec3 lPos = glm::vec3(-5, 5, 0);
	glm::vec3 lightDir(sin(glfwGetTime()), 1, cos(glfwGetTime()));

	// Update material
	m_spear->Bind();
	m_spearMat->ApplyUniformMat4("projectionViewMatrix", projView);
	m_spearMat->ApplyUniformMat4("modelMatrix", m_spear->m_transform.WorldMatrix());
	// m_spearMat->ApplyUniformVec3("camPos", m_camera->m_position);
	// m_spearMat->ApplyUniformVec3("L", glm::normalize(lPos - m_camera->m_position));
	m_spearMat->ApplyUniformVec3("lightDirection", lightDir);
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
	//glUseProgram(m_tintTexObjShader->GetProgramID());

	//// set texture slot
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_signDiffuse->GetID());
	//// tell the shader where it is 
	//unsigned int texLoc1 = glGetUniformLocation(m_tintTexObjShader->GetProgramID(), "diffuse");
	//if (texLoc1 < 0) { LOG_ERROR("glGetUniformLocation( diffuse ) failed.") }
	//glUniform1i(texLoc1, 0);

	//int PVMatLoc3 = glGetUniformLocation(m_tintTexObjShader->GetProgramID(), "projectionViewMatrix");
	//glUniformMatrix4fv(PVMatLoc3, 1, false, glm::value_ptr(projView));
	//int modelMatLoc3 = glGetUniformLocation(m_tintTexObjShader->GetProgramID(), "modelMatrix");
	//glUniformMatrix4fv(modelMatLoc3, 1, false, glm::value_ptr(m_signTransform->WorldMatrix()));

	//m_signRenderData->Render();

	//// Spear
	//glBindTexture(GL_TEXTURE_2D, m_texSpearDiffuse->GetID());
	//// glUniform1i() 0 is for GL_TEXTURE0. 1 is for GL_TEXTURE1
	//glUniform1i(texLoc1, 0);

	//glUseProgram(0);

	return 0;
}

