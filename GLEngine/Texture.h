#pragma once

#include <string>
class Texture
{
public:
	Texture(const std::string& _path);
	~Texture();

	Texture(const Texture& _other) = delete;
	Texture(Texture&& _other);

	Texture& operator=(const Texture& _other) = delete;

#pragma region Getters
	unsigned int GetID() const { return m_id; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	int GetFormat() const { return m_format; }
	const unsigned char* const GetData() const { return m_data; }
	const std::string& GetPath() const { return m_path; }
#pragma endregion Getters

private:
	void LoadTexture();

	unsigned int m_id;
	int m_width,
		m_height,
		m_format;

	unsigned char* m_data;

	std::string m_path;
};
