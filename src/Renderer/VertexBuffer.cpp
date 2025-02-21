#include "VertexBuffer.h"

namespace RenderEngine
{
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_index);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& buffer) noexcept
	{
		m_index = buffer.m_index;
		buffer.m_index = 0;
	}

	VertexBuffer& VertexBuffer::operator = (VertexBuffer&& buffer) noexcept
	{
		m_index = buffer.m_index;
		buffer.m_index = 0;
		return *this;
	}

	void VertexBuffer::init(const void* data, const unsigned int size)
	{
		glGenBuffers(1, &m_index);
		glBindBuffer(GL_ARRAY_BUFFER, m_index);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::update(const void* data, const unsigned int size) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_index);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_index);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}