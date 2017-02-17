#include "DEGUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "ApplicationDemo.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "ShaderProgram.h"
#include "Shaders1.h"
#include "Mesh.h"


ApplicationDemo::ApplicationDemo()
	: ApplicationBase("Game Engine Demo", 1280, 720) {}

ApplicationDemo::~ApplicationDemo() {}

int ApplicationDemo::Start()
{
	if (ApplicationBase::Start()) return -1;

	SetBackgroundColor(0.25f, 0.25f, 0.25f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_shaderProgram = new ShaderProgram(
		new VertexShader(vsSource),
		new FragmentShader(fsSource));

	m_camera = new Camera();
	m_camera->SetAsMain();

	m_quad = Primatives::Plane(20, 20);
	m_sphere = Primatives::Sphere(10, 33, 33);

	m_camera->SetPos({ 0, 20,	50 });
	m_camera->SetDir({ 0, -0.5, -1 });
	m_camera->UpdateView();
	_bounceDir = 1;

	return 0;
}

int ApplicationDemo::Shutdown()
{
	if (ApplicationBase::Shutdown()) return -1;

	delete m_sphere;
	delete m_quad;
	delete m_camera;
	delete m_shaderProgram;

	return 0;
}

int ApplicationDemo::Update(double _deltaTime)
{
	if (ApplicationBase::Update(_deltaTime)) return -1;

	// Bounce Camera
	if (m_camera->m_direction.x > 0.5f || m_camera->m_direction.x < -0.5f)
		_bounceDir = -_bounceDir;
	m_camera->m_direction.x += (float)(_bounceDir * 0.4 * _deltaTime);
	m_camera->UpdateView();

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	glm::mat4 projView = GLE::MAIN_CAM->m_projection * GLE::MAIN_CAM->m_view;

	m_sphere->DrawMesh(m_shaderProgram, &projView);
	m_quad->DrawMesh(m_shaderProgram, &projView);

	return 0;
}

