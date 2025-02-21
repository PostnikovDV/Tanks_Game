#pragma once
#include <glad/glad.h>

namespace RenderEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator = (const IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& buffer) noexcept;
		IndexBuffer& operator = (IndexBuffer&& buffer) noexcept;

		void init(const void* data, const unsigned int count);

		void bind() const;
		void unbind() const;
		unsigned int getCount() const { return m_count; }

	private:
		GLuint m_index{ 0 };
		unsigned int m_count{ 0 };
	};
}
