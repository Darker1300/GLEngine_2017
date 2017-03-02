#include "DEBUG_NEW_LEAK_DETECT.h"
#include "DEBUG_WINDOWS_ERR_MSG.h"

#include "GeometryHelper.h"

#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include "RenderData.h"
#include "tiny_obj_loader.h"

namespace GeometryHelper {
	RenderData * CreatePlane(const unsigned int _rows, const unsigned int _cols, const float _width, const float _height, const glm::vec4& _colour)
	{
		// Vertices
		unsigned int verticesSize = _rows * _cols;
		SimpleVertex* vertices = new SimpleVertex[verticesSize];
		float colSpacing = _width / (_cols - 1);
		float rowSpacing = _height / (_rows - 1);

		float uvFactorX = 1.0f / (_cols - 1);
		float uvFactorY = 1.0f / (_rows - 1);

		// Vertices Generation
		for (unsigned int r = 0; r < _rows; r++)
		{
			for (unsigned int c = 0; c < _cols; c++)
			{
				SimpleVertex& vert = vertices[r * _cols + c];
				// Pos
				vert.position = glm::vec4(
					-(_width / 2) + (colSpacing * c), 0,
					-(_height / 2) + (rowSpacing * r), 1);
				// Colour
				vert.colour = _colour;
				// UVs
				vert.uv = glm::vec2(
					c * uvFactorX,
					r * uvFactorY);
			}
		}
		// Indices
		unsigned int indicesSize = (_rows - 1) * (_cols - 1) * 6;
		unsigned int* indices = new unsigned int[indicesSize];

		// Indices Generation
		unsigned int index = 0;
		for (unsigned int r = 0; r < (_rows - 1); ++r)
		{
			for (unsigned int c = 0; c < (_cols - 1); ++c)
			{
				// Triangle 1
				indices[index++] = r * _cols + c;
				indices[index++] = (r + 1) * _cols + c;
				indices[index++] = (r + 1) * _cols + (c + 1);
				// Triangle 2
				indices[index++] = r * _cols + c;
				indices[index++] = (r + 1) * _cols + (c + 1);
				indices[index++] = r * _cols + (c + 1);
			}
		}

		// Store on GPU
		RenderData* renderData = new RenderData();
		renderData->GenerateBuffers();

		// Bind VAO (includes VBO & IBO)
		renderData->Bind();
		// Send Vertices
		glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(SimpleVertex), vertices, GL_STATIC_DRAW);
		// Send Indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		// Let OpenGL know where to find the data in the vertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(SimpleVertex),
			(char*)offsetof(SimpleVertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(SimpleVertex),
			(char*)offsetof(SimpleVertex, colour));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(SimpleVertex),
			(char*)offsetof(SimpleVertex, uv));

		// Unbind VAO (includes VBO & IBO)
		renderData->Unbind();

		// Configure RenderData
		renderData->SetIndicesSize(indicesSize);
		renderData->SetPrimitiveType(GL_TRIANGLES);

		// Delete cpu-side data
		delete[] vertices;
		delete[] indices;

		return renderData;
	}

	RenderData * CreateQuad(const float _width, const float _height, glm::vec3 facingDirection, const glm::vec4& _colour)
	{
		return nullptr;
	}

	std::vector<RenderData*> LoadOBJFromDisk(const std::string& _path)
	{
		tinyobj::attrib_t attribs;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		// Load
		bool success = tinyobj::LoadObj(&attribs, &shapes, &materials, &err, _path.c_str());
		if (!success) { LOG_ERROR("Could not load OBJ correctly. Path: ", _path, ".") }

		// Parse
		std::vector<RenderData*> modelRenderData;
		modelRenderData.reserve(shapes.size());

		// grab each shape
		int shapeIndex = 0;
		for (auto& shape : shapes) {

			// collect triangle vertices
			std::vector<OBJVertex> vertices;
			int index = 0;
			for (auto face : shape.mesh.num_face_vertices)
			{
				for (int i = 0; i < 3; ++i)
				{
					tinyobj::index_t idx = shape.mesh.indices[index + i];
					OBJVertex v = { {},{},{} };
					// positions
					v.position.x = attribs.vertices[3 * idx.vertex_index + 0];
					v.position.y = attribs.vertices[3 * idx.vertex_index + 1];
					v.position.z = attribs.vertices[3 * idx.vertex_index + 2];
					v.position.w = 1;
					// normals
					if (attribs.normals.size() > 0)
					{
						v.normal.x = attribs.normals[3 * idx.normal_index + 0];
						v.normal.y = attribs.normals[3 * idx.normal_index + 1];
						v.normal.z = attribs.normals[3 * idx.normal_index + 2];
					} // texture coordinates
					if (attribs.texcoords.size() > 0)
					{
						v.uv.s = attribs.texcoords[2 * idx.texcoord_index + 0];
						v.uv.t = attribs.texcoords[2 * idx.texcoord_index + 1];
					}
					vertices.push_back(v);
				}
				index += face;
			}
			// Parse shape to GPU
			RenderData* renderData = new RenderData();
			modelRenderData.push_back(renderData);
			// Set indices size (in this case == vertices size)
			renderData->SetIndicesSize(vertices.size());
			renderData->GenerateBuffers(false);
			renderData->Bind();

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OBJVertex), vertices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)offsetof(OBJVertex, OBJVertex::position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)offsetof(OBJVertex, OBJVertex::normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), (void*)offsetof(OBJVertex, OBJVertex::uv));

			renderData->Unbind();

		}

		return modelRenderData;
	}
}
