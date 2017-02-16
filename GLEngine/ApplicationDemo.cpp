#include "ApplicationDemo.h"

#include <gl_core_4_4.h>
#include <GlFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"
#include "ShaderProgram.h"
#include "Shaders1.h"

ApplicationDemo::ApplicationDemo()
	: ApplicationBase()
{
	sProgram = nullptr;
}

ApplicationDemo::~ApplicationDemo()
{
	delete sProgram;
}

int ApplicationDemo::Start()
{
	sProgram = new ShaderProgram(
		VertexShader(vsSource),
		FragmentShader(fsSource));


	return ApplicationBase::Start();
}

int ApplicationDemo::Update(double _deltaTime)
{

	return ApplicationBase::Update(_deltaTime);
}

int ApplicationDemo::Draw()
{
	glm::mat4 projView = GLE::MAIN_CAM->m_projection * GLE::MAIN_CAM->m_view;

	glUseProgram(sProgram->m_programID);
	unsigned int projectionViewGlobalLocation
		= glGetUniformLocation(sProgram->m_programID, "projectionViewGlobalMatrix");
	if (projectionViewGlobalLocation != -1)
	{
		ERROR_MSG("glGetUniformLocation(projectionViewGlobalMatrix) failed.");
	}

	glUniformMatrix4fv(projectionViewGlobalLocation, 1, false,
		glm::value_ptr(projView));


	return ApplicationBase::Draw();
}

int ApplicationDemo::Shutdown()
{

	return ApplicationBase::Shutdown();
}
