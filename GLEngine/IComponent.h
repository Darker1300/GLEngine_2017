
#pragma once

class IComponent
{
public:
	IComponent() {}
	virtual ~IComponent() {}

	virtual void Update() {}
	virtual void Render() {}
};
