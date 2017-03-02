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

ApplicationDemo::ApplicationDemo()
	: ApplicationBase("Game Engine Demo", 1280, 720) {}

ApplicationDemo::~ApplicationDemo() {}

int ApplicationDemo::Start()
{
	if (ApplicationBase::Start()) return -1;

	SetBackgroundColor(0.25f, 0.25f, 0.25f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	{
//		using namespace gl;
//#define SHADER_CURRENT SHADER_TEX
//		m_shaderProgram = new ShaderProgram(
//			new VertexShader(SHADER_CURRENT::vertexSource),
//			new FragmentShader(SHADER_CURRENT::fragmentSource),
//			SHADER_CURRENT::uniforms,
//			SHADER_CURRENT::uniformsCount
//		);
//	}

	m_camera = new FlyCamera(GetWindow(), 10);

	m_camera->SetPerspective(
		glm::pi<float>() * 0.25f,
		(float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight(),
		0.1f, 1000.0f);
	//m_camera->LookAt(
	//	glm::vec3(0, 0, 0),
	//	glm::vec3(0, 0, 1),
	//	glm::vec3(0, 1, 0));
	m_camera->m_transform.Translate({0, 1, 3});
	m_camera->SetAsMain();

	/*m_quad = Primatives::Plane(20, 20);
	m_sphere = Primatives::Sphere(4, 33, 33);*/

	m_planeShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");
	m_planeRenderData = GeometryHelper::CreatePlane(10, 10, 10, 10, { 1,0.3f,0,1 });

	m_objShader = new Shader("./shaders/basicOBJ.vert", "./shaders/basicOBJ.frag");
	m_dragonRenderData = GeometryHelper::LoadOBJFromDisk("./models/deer.obj");
	m_dragonTransform = new Transform();
	m_dragonTransform->Scale(0.005f);

	m_ianShader = new Shader("./shaders/ian.vert", "./shaders/ian.frag");
	m_ianRenderData = GeometryHelper::CreatePlane(2, 2, 4, 2, { 1,1,1,1 });
	m_texIan = gl::Texture::Load("./textures/ian.png");
	m_ianTransform = new Transform();
	// m_ianTransform->SetParent(m_dragonTransform);
	m_ianTransform->Translate(-m_ianTransform->Forward() * 5);
	m_ianTransform->Rotate({ 3.14159265f * 0.5f, 0, 0 });

	//m_texTest = gl::Texture::Load("./textures/ship_ori.png");


	//m_camera->SetPos({ 0, 20,	50 });
	//m_camera->SetDir({ 0, -0.5, -1 });
	//m_camera->UpdateView();
	//_bounceDir = 1;

	return 0;
}

int ApplicationDemo::Shutdown()
{
	if (ApplicationBase::Shutdown()) return -1;

	delete m_planeRenderData;
	delete m_planeShader;
	//delete m_texTest;

	delete m_texIan;
	delete m_ianRenderData;
	delete m_ianTransform;

	delete m_objShader;
	delete m_dragonTransform;
	for (RenderData* data : m_dragonRenderData)
		delete data;

	//delete m_sphere;
	//delete m_quad;
	delete m_camera;
	//delete m_shaderProgram;

	return 0;
}

int ApplicationDemo::FixedUpdate(double _deltaTime)
{
	if (ApplicationBase::FixedUpdate(_deltaTime)) return -1;
	//m_ianTransform->Rotate({ 0,1 * _deltaTime,0 });
	//// Bounce Camera
	//static float Range = 0.5;
	//if (m_camera->m_direction.x > Range || m_camera->m_direction.x < -Range)
	//	_bounceDir = -_bounceDir;
	//m_camera->m_direction.x += (float)(_bounceDir * 0.4 * _deltaTime);

	return 0;
}

int ApplicationDemo::Update(double _deltaTime)
{
	if (ApplicationBase::Update(_deltaTime)) return -1;

	m_camera->Update((float)_deltaTime);

	//m_dragonTransform->Rotate({ 0, -1 * _deltaTime,0 });
	// Bounce Camera
	/*m_camera->UpdateView();*/

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	//glm::mat4 projView = GLE::MAIN_CAM->m_projection * GLE::MAIN_CAM->m_view;
	glm::mat4 projView = m_camera->GetProjectionViewWorld();

	// Plane
	glUseProgram(m_planeShader->GetProgramID());
	// Set Uniform
	int PVMatLoc1 = glGetUniformLocation(m_planeShader->GetProgramID(), "projectionViewMatrix");
	glUniformMatrix4fv(PVMatLoc1, 1, false, glm::value_ptr(projView));

	 m_planeRenderData->Render();

	// OBJ
	glUseProgram(m_objShader->GetProgramID());
	// Set Uniform
	int PVMatLoc2 = glGetUniformLocation(m_objShader->GetProgramID(), "projectionViewMatrix");
	glUniformMatrix4fv(PVMatLoc2, 1, false, glm::value_ptr(projView));
	int modelMatLoc2 = glGetUniformLocation(m_objShader->GetProgramID(), "modelMatrix");
	glUniformMatrix4fv(modelMatLoc2, 1, false, glm::value_ptr(m_dragonTransform->WorldMatrix()));

	for (RenderData*& data : m_dragonRenderData)
		data->Render();

	// Ian
	glUseProgram(m_ianShader->GetProgramID());

	// set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texIan->m_id);
	// tell the shader where it is 
	unsigned int texLoc1 = glGetUniformLocation(m_ianShader->GetProgramID(), "diffuse");
	if (texLoc1 < 0) { LOG_ERROR("glGetUniformLocation( diffuse ) failed.") }
	glUniform1i(texLoc1, 0);

	int PVMatLoc3 = glGetUniformLocation(m_ianShader->GetProgramID(), "projectionViewMatrix");
	glUniformMatrix4fv(PVMatLoc3, 1, false, glm::value_ptr(projView));
	int modelMatLoc3 = glGetUniformLocation(m_ianShader->GetProgramID(), "modelMatrix");
	glUniformMatrix4fv(modelMatLoc3, 1, false, glm::value_ptr(m_ianTransform->WorldMatrix()));

	m_ianRenderData->Render();

	glUseProgram(0);

	return 0;
}

