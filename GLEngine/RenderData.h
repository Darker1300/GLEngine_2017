#pragma once
class RenderData
{
public:
	RenderData();
	~RenderData();

	RenderData(const RenderData& _other) = delete;
	RenderData(RenderData&& _other);

	RenderData& operator=(const RenderData& _other) = delete;

	void GenerateBuffers();
	void Render() const;
	void Bind() const;
	void Unbind() const;

	unsigned int& GetVAO() { return m_VAO; }
	unsigned int& GetVBO() { return m_VBO; }
	unsigned int& GetIBO() { return m_IBO; }

	unsigned int GetVAO() const { return m_VAO; }
	unsigned int GetVBO() const { return m_VBO; }
	unsigned int GetIBO() const { return m_IBO; }

	unsigned int GetPrimitiveType() const {}
	unsigned int GetIndicesSize() const {}

	void SetPrimitiveType(const unsigned int _type) { m_primitiveType = _type; }
	void SetIndicesSize(const unsigned int _size) { m_indicesSize = _size; }


private:
	void DestroyBuffers();

	unsigned int
		m_VAO,
		m_VBO,
		m_IBO,
		m_primitiveType,
		m_indicesSize;
};

