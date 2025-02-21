#include "VertexArray.h"

namespace RenderEngine
{
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_index);
	}

	VertexArray::VertexArray(VertexArray&& buffer) noexcept
	{
		m_index = buffer.m_index;
		buffer.m_index = 0;
	}

	VertexArray& VertexArray::operator = (VertexArray&& buffer) noexcept
	{
		m_index = buffer.m_index;
		buffer.m_index = 0;
		return *this;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_index);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
	{
		bind();
		buffer.bind();
		const auto& layoutElements = layout.getLayoutElements();
		GLbyte* offset = nullptr;
		for (int i = 0; i < layoutElements.size(); i++)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = m_elementsCount + i;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);

			offset += currentLayoutElement.size;
		}
		m_elementsCount += layoutElements.size();
	}
}