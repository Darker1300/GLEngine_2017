#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "RenderableObject.h"

#include "Material.h"
#include "RenderData.h"

RenderableObject::RenderableObject(Material * _material, std::vector<RenderData*>& _renderShapes)
	: m_material(_material), m_renderShapes(_renderShapes)
{
}

RenderableObject::~RenderableObject()
{
}

void RenderableObject::Bind() const
{
	m_material->Bind();
}

void RenderableObject::Render()
{
	for (RenderData* data : m_renderShapes) {
		data->Bind();
		data->Render();
	}
}

void RenderableObject::Unbind() const
{
	m_material->Unbind();
	RenderData::Unbind();
}
