#include "VertexBufferLayout.h"

namespace RenderEngine
{
	void VertexBufferLayout::addElementLayout(const int count, const bool normalize)
	{
		m_layoutElements.push_back({ count, GL_FLOAT, normalize, count * sizeof(GLfloat) });
		m_stride += m_layoutElements.back().size;
	}

	void VertexBufferLayout::reserveElements(const size_t count)
	{
		m_layoutElements.reserve(count);
	}
}
