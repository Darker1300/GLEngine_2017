#include "VertexArray.h"

#include <gl_core_4_4.h>
#include <climits>

gl::VertexArray::VertexArray()
{

}


gl::VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_B_Vertex_ID);
	glDeleteBuffers(1, &m_B_Index_ID);
	glDeleteBuffers(1, &m_A_Vertex_ID);
}
