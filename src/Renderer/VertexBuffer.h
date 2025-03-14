#pragma once
#include <glad/glad.h>

namespace RenderEngine
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator = (const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& buffer) noexcept;
		VertexBuffer& operator = (VertexBuffer&& buffer) noexcept;

		void init(const void* data, const unsigned int size);

		void update(const void* data, const unsigned int size) const;

		void bind() const;
		void unbind() const;

	private:
		GLuint m_index{ 0 };
	};
}
