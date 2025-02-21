#include "IndexBuffer.h"

namespace RenderEngine
{
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_index);
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& buffer) noexcept
	{
		m_index = buffer.m_index;
		m_count = buffer.m_count;
		buffer.m_index = 0;
		buffer.m_count = 0;
	}

	IndexBuffer& IndexBuffer::operator = (IndexBuffer&& buffer) noexcept
	{
		m_index = buffer.m_index;
		m_count = buffer.m_count;
		buffer.m_index = 0;
		buffer.m_count = 0;
		return *this;
	}

	void IndexBuffer::init(const void* data, const unsigned int count)
	{
		m_count = count;
		glGenBuffers(1, &m_index);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}