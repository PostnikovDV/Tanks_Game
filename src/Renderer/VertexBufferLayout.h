#pragma once
#include <glad/glad.h>
#include <vector>

namespace RenderEngine
{
	struct VertexBufferLayoutElement
	{
		GLint count;
		GLenum type;
		GLboolean normalized;
		size_t size;
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout() = default;

		void addElementLayout(const int count, const bool normalize);

		void reserveElements(const size_t count);

		unsigned int getStride() const { return m_stride; }

		const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; }

	private:
		std::vector<VertexBufferLayoutElement> m_layoutElements;

		unsigned int m_stride{ 0 };
	};
}