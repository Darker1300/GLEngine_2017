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
#include "Model.h"


ApplicationDemo::ApplicationDemo()
	: ApplicationBase("Game Engine Demo", 1280, 720) {}

ApplicationDemo::~ApplicationDemo() {}

int ApplicationDemo::Start()
{
	if (ApplicationBase::Start()) return -1;

	SetBackgroundColor(0.25f, 0.25f, 0.25f);

	m_shaderProgram = new ShaderProgram(
		new VertexShader(vsSource),
		new FragmentShader(fsSource));

	m_camera = new Camera();
	m_camera->SetAsMain();

	m_quad = new Model();
	m_quad->GeneratePlane(2, 2);

	return 0;
}

int ApplicationDemo::Shutdown()
{
	if (ApplicationBase::Shutdown()) return -1;

	delete m_quad;
	delete m_camera;
	delete m_shaderProgram;

	return 0;
}

int ApplicationDemo::Update(double _deltaTime)
{
	if (ApplicationBase::Update(_deltaTime)) return -1;

	return 0;
}

int ApplicationDemo::Draw()
{
	if (ApplicationBase::Draw()) return -1;

	glm::mat4 projView = GLE::MAIN_CAM->m_projection * GLE::MAIN_CAM->m_view;

	m_quad->DrawModel(m_shaderProgram, &projView);

	return 0;
}

