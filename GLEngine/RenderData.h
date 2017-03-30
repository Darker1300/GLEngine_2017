#pragma once
class RenderData
{
public:
	RenderData();
	~RenderData();

	RenderData(const RenderData& _other) = delete;
	RenderData(RenderData&& _other);

	RenderData& operator=(const RenderData& _other) = delete;

	void GenerateBuffers(bool _generateIndexBuffer = true);

	template <typename T>
	void FillVertexBuffer(T* _first, unsigned _count);
	void FillIndexBuffer(unsigned int* _first, unsigned _count);

	void SetFloatAttributePointer(unsigned _slot, unsigned _floatCount, unsigned _vertexSize, unsigned _vertexMemberOffset);

	void Render() const;
	void Bind() const;
	static void Unbind();

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
	bool m_hasIndexBuffer;
};

template<typename T>
inline void RenderData::FillVertexBuffer(T * _first, unsigned _count)
{
	SetIndicesSize(_count);
	// Bind
	Bind();
	// Send Vertices
	glBufferData(GL_ARRAY_BUFFER, _count * sizeof(T), _first, GL_STATIC_DRAW);
}
