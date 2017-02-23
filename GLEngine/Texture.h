#pragma once


namespace gl {

	class Texture
	{
	public:
		Texture();
		~Texture();

		static Texture* Load(const char* const _path);


		int m_width;
		int m_height;
		int m_format;
		unsigned char* m_data;

		unsigned int m_id;

	};
}

