#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public: 
		static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shaderProgram);

		static void setClearColor(float r, float g, float b, float alpha);

		static void setClear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
		static void setViewport(unsigned int Width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0)
		{
			glViewport(leftOffset, bottomOffset, Width, height);
		}

		static void setDepthTest(const bool enable);

		static std::string getRendererStr() { return (char*)glGetString(GL_RENDERER); }
		static std::string getVersionStr() { return (char*)glGetString(GL_VERSION); }
	};
}