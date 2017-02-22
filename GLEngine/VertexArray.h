#pragma once
#include <map>

namespace gl {
	class SHADER_BASE;

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		union {
			struct {
				unsigned int m_B_Vertex_ID;
				unsigned int m_B_Index_ID;
				unsigned int m_A_Vertex_ID;
			};
			unsigned int m_IDs[3];
		};

	private:
		void bind_BV();
		void bind_BI();
		void bind_AV();

		void gen_BV();
		void gen_BI();
		void gen_AV();
	};
}
