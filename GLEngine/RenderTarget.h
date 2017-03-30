#pragma once

class Texture;

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	RenderTarget(const RenderTarget& _other) = delete;
	RenderTarget(RenderTarget&& _other);

	RenderTarget& operator=(const RenderTarget& _other) = delete;

	void Generate(unsigned int _width, unsigned int _height);
	void Bind();
	void Unbind();

	unsigned int m_frameBufferID;
	Texture* m_colour;
	Texture* m_depth;

private:
	unsigned int CreateTexture2D(const int w, const int h, int, unsigned int format, unsigned int type);
	bool CreateFBO(const int w, const int h);
};
