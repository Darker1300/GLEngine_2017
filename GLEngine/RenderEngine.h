
#pragma once

class RenderEngine
{
	friend class Core;
public:

protected:
	static void Initialize();
	static void Finalize();

	RenderEngine();
	~RenderEngine();

};
