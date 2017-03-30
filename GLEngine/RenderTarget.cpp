#include "RenderTarget.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include <gl_core_4_4.h>
#include "ApplicationBase.h"
#include "Texture.h"


RenderTarget::RenderTarget()
	: m_frameBufferID(-1)
	, m_colour(new Texture())
	, m_depth(new Texture())
{
}


RenderTarget::~RenderTarget()
{
	delete m_colour;
	delete m_depth;
}

RenderTarget::RenderTarget(RenderTarget && _other)
{
	m_frameBufferID = _other.m_frameBufferID;
	delete m_colour;
	m_colour = _other.m_colour;
	delete m_depth;
	m_depth = _other.m_depth;
	_other.m_frameBufferID = -1;
	_other.m_depth = nullptr;
	_other.m_colour = nullptr;
}

void RenderTarget::Generate(unsigned int _width, unsigned int _height)
{
	m_colour->m_width = _width;
	m_colour->m_height = _height;
	m_depth->m_width = _width;
	m_depth->m_height = _height;

	CreateFBO(_width, _height);
}

void RenderTarget::Bind()
{
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);
	//glDrawBuffer(GL_NONE);
	glViewport(0, 0, m_colour->m_width, m_colour->m_height);
	// clear old capture
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTarget::Unbind()
{
	// bind the back-buffer 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GLE::APP->GetWindowWidth(), GLE::APP->GetWindowHeight());
}

unsigned int RenderTarget::CreateTexture2D(const int w, const int h, int internalFormat, unsigned int format, unsigned int type)
{
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//NOTE: You should use GL_NEAREST here. Other values can cause problems
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (GL_DEPTH_COMPONENT == format) {
		//sample like regular texture, value is in all channels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		// glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_COMPONENT, GL_INTENSITY);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, type, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureId;
}

bool RenderTarget::CreateFBO(const int w, const int h)
{
	bool result = false;
	//generate textures for FBO usage. You could use other formats here, e.g. GL_RGBA8 for color
	m_colour->m_id = CreateTexture2D(w, h, GL_RGBA16F, GL_RGBA, GL_FLOAT);
	m_depth->m_id = CreateTexture2D(w, h, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
	//generate and bind FBO
	glGenFramebuffers(1, &m_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	//bind color and depth texture to FBO you could also use glFramebufferTexture2D with GL_TEXTURE_2D
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colour->m_id, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth->m_id, 0);
	//check if FBO was created ok
	if (GL_FRAMEBUFFER_COMPLETE == glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
		printf("FBO %d set up successfully. Yay!\n", m_frameBufferID);
		result = true;
	}
	else {
		printf("FBO %d NOT set up properly!\n", m_frameBufferID);
	}
	//unbind FBO for now
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return result;
}
