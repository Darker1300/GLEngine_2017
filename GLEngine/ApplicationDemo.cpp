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

ApplicationDemo::ApplicationDemo()
	: ApplicationBase("Game Engine Demo", 1280, 720) {}

ApplicationDemo::~ApplicationDemo() {}

int ApplicationDemo::Start()
{
	if (ApplicationBase::Start()) return -1;

	SetBackgroundColor(0.25f, 0.25f, 0.25f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	{
		using namespace gl;
#define SHADER_CURRENT SHADER_TEX
		m_shaderProgram = new ShaderProgram(
			new VertexShader(SHADER_CURRENT::vertexSource),
			new FragmentShader(SHADER_CURRENT::fragmentSource),
			SHADER_CURRENT::uniforms,
			SHADER_CURRENT::uniformsCount
		);
	}

	m_camera = new FlyCamera(GetWindow(), 10);

	m_camera->SetPerspective(
		glm::pi<float>() * 0.25f,
		(float)GLE::APP->GetWindowWidth() / (float)GLE::APP->GetWindowHeight(),
		0.1f, 1000.0f);
	m_camera->LookAt(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 1, 0));
	//m_camera->SetAsMain();S

	m_quad = Primatives::Plane(20, 20);
	m_sphere = Primatives::Sphere(4, 33, 33);
	m_tex = gl::Texture::Load("./textures/ship_ori.png");
	//m_camera->SetPos({ 0, 20,	50 });
	//m_camera->SetDir({ 0, -0.5, -1 });
	//m_camera->UpdateView();
	//_bounceDir = 1;

	m_planeRenderData = GeometryHelper::CreateGrid(10, 10, 10, 10, { 1,0.3f,0,1 });
	m_planeShader = new Shader("./shaders/basic.vert", "./shaders/basic.frag");

	return 0;
}

int ApplicationDemo::Shutdown()
{
	if (ApplicationBase::Shutdown()) return -1;

	delete m_planeShader;
	delete m_planeRenderData;
	delete m_tex;
	delete m_sphere;
	delete m_quad;
	delete m_camera;
	delete m_shaderProgram;

	return 0;
}

int ApplicationDemo::FixedUpdate(double _deltaTime)
{
	if (ApplicationBase::FixedUpdate(_deltaTime)) return -1;

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
	// Bounce Camera
	/*m_camera->UpdateView();*/

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	//glm::mat4 projView = GLE::MAIN_CAM->m_projection * GLE::MAIN_CAM->m_view;
	glm::mat4 projView = m_camera->GetWorldProjectionView();



	glUseProgram(m_planeShader->GetProgramID());

	int loc = glGetUniformLocation(m_planeShader->GetProgramID(), "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(projView));

	m_planeRenderData->Render();


	//m_sphere->DrawMesh(m_shaderProgram, &projView, m_tex);
	//m_quad->DrawMesh(m_shaderProgram, &projView, m_tex);

	return 0;
}

