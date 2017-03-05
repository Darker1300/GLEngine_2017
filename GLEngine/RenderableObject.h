#pragma once

class Material;
class RenderData;

#include "Transform.h"
#include <vector>

class RenderableObject
{
public:
	RenderableObject(Material* _material, std::vector<RenderData*>& _renderShapes);

	// TODO COPY/MOVE

	~RenderableObject();

	void Bind() const;
	void Render();
	static void Unbind();

	Material* m_material;
	std::vector<RenderData*> m_renderShapes;
	Transform m_transform;
};

