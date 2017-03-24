#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "Texture.h"

#include <gl_core_4_4.h>
#include <stb_image.h>

Texture::Texture()
	:
	//m_path(""),
	m_id(-1)
	, m_width(0)
	, m_height(0)
	, m_format(-1)
	, m_data(nullptr)
	, m_flipY(false)
{
}

Texture::Texture(const std::string & _path, const bool _flipY /*= true*/)
	:// m_path(_path) ,
	m_id(-1)
	, m_width(0)
	, m_height(0)
	, m_format(-1)
	, m_data(nullptr)
	, m_flipY(_flipY)
{
	LoadTexture(_path, m_flipY);
}

Texture::~Texture()
{
	if (m_data != nullptr) stbi_image_free(m_data);
}

Texture::Texture(Texture && _other)
{
	m_id = _other.m_id;
	m_width = _other.m_width;
	m_height = _other.m_height;
	m_format = _other.m_format;
	m_data = _other.m_data;
	//m_path = _other.m_path;
	_other.m_id = -1;
	_other.m_data = nullptr;
}

void Texture::LoadTexture(const std::string& _path, const bool _flipY)
{
	m_flipY = _flipY;
	//m_path = _path;

	// Set Y flip option
	stbi_set_flip_vertically_on_load(m_flipY);
	// Load
	m_data = stbi_load(_path.c_str(), &m_width, &m_height, &m_format, STBI_default);
	if (m_data == nullptr) {
		LOG_ERROR("STBI failed to load image at:\n ", _path, ".");
		return;
	}

	// Set Color channel structure
	int internalFormat = 0;
	switch (m_format)
	{
	case 1:
		internalFormat = GL_RED;
		break;
	case 2:
		internalFormat = GL_RG;
		break;
	case 3:
		internalFormat = GL_RGB;
		break;
	case 4:
		internalFormat = GL_RGBA;
		break;
	default:
		LOG_ERROR("STBI's internal format changed!");
		break;
	}

	// Generate
	glGenTextures(1, &m_id);
	// Bind
	glBindTexture(GL_TEXTURE_2D, m_id);
	// Move to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, internalFormat, GL_UNSIGNED_BYTE, m_data);

	// Set Textures parameters for currently bound
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

}
