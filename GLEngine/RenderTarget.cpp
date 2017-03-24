#include "RenderTarget.h"

#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include <gl_core_4_4.h>
#include "ApplicationBase.h"
#include "Texture.h"


RenderTarget::RenderTarget()
	: m_frameBufferID(-1)
	, m_texture(new Texture())
	, m_depth(new Texture())
{
}


RenderTarget::~RenderTarget()
{
	delete m_texture;
	delete m_depth;
}

RenderTarget::RenderTarget(RenderTarget && _other)
{
	m_frameBufferID = _other.m_frameBufferID;
	delete m_texture;
	m_texture = _other.m_texture;
	delete m_depth;
	m_depth = _other.m_depth;
	_other.m_frameBufferID = -1;
	_other.m_depth = nullptr;
	_other.m_texture = nullptr;
}

void RenderTarget::Generate(unsigned int _width, unsigned int _height)
{
	m_texture->m_width = _width;
	m_texture->m_height = _height;
	m_depth->m_width = _width;
	m_depth->m_height = _height;

	// setup framebuffer
	// Frame Buffer
	glGenFramebuffers(1, &m_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	// Texture Generation
	glGenTextures(1, &m_texture->m_id);
	// Texture Bind
	glBindTexture(GL_TEXTURE_2D, m_texture->m_id);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, _width, _height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture->m_id, 0);

	// The depth buffer
	glGenRenderbuffers(1, &m_depth->m_id);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depth->m_id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth->m_id);

	// Set the list of draw buffers.
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

	// Check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG_ERROR("Framebuffer did not generate correctly.");
	}

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTarget::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	glViewport(0, 0, m_texture->m_width, m_texture->m_height);
	// clear old capture
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
}

void RenderTarget::Unbind()
{
	// bind the back-buffer 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GLE::APP->GetWindowWidth(), GLE::APP->GetWindowHeight());

	//glClear(GL_DEPTH_BUFFER_BIT);
}
