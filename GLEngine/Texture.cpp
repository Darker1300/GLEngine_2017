#include "Texture.h"

#include <gl_core_4_4.h>
#include <stb_image.h>

using namespace gl;

Texture::Texture()
{
}

Texture::~Texture()
{
	stbi_image_free(m_data);
}

Texture * Texture::Load(const char * const _path)
{
	Texture* uv = new Texture();
	uv->m_data = stbi_load(_path,
		&uv->m_width, &uv->m_height, &uv->m_format, STBI_default);

	glGenTextures(1, &uv->m_id);

	glBindTexture(GL_TEXTURE_2D, uv->m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, uv->m_width, uv->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, uv->m_data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return uv;
}
