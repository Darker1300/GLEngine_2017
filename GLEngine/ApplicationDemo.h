#pragma once

class ShaderProgram;

#include "ApplicationBase.h"

class ApplicationDemo : public ApplicationBase
{
public:
	ApplicationDemo();
	~ApplicationDemo();

	virtual int Start();
	virtual int Update(double _deltaTime);
	virtual int Draw();
	virtual int Shutdown();

protected:
	ShaderProgram* sProgram;
};
