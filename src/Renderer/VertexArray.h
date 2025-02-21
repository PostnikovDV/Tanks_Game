#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RenderEngine
{
	class VertexArray
	{
	public:
		VertexArray() { glGenVertexArrays(1, &m_index); }
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator = (const VertexArray&) = delete;

		VertexArray(VertexArray&& buffer) noexcept;
		VertexArray& operator = (VertexArray&& buffer) noexcept;

		void bind() const;
		void unbind() const;
		void addBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

	private:
		GLuint m_index{ 0 };

		size_t m_elementsCount{ 0 };
	};
}
