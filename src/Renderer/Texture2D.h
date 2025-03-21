#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RenderEngine
{
	class Texture2D
	{
	public:


		struct SubTexture2D
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2D(glm::vec2 _leftBottomUV, glm::vec2 _rightTopUV) : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV)
			{

			}

			SubTexture2D() : leftBottomUV(0.f), rightTopUV(1.f)
			{

			}
		};


		Texture2D(const GLuint Width, const GLuint height, 
			const unsigned char* data, 
			const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE
		);
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator = (const Texture2D&) = delete;
		Texture2D(Texture2D&& texture2D) noexcept;
		Texture2D& operator = (Texture2D&& texture2D) noexcept;
		~Texture2D();

		void addSubTexture2D(std::string name, glm::vec2& leftBottomUV, glm::vec2& rightTopUV);

		const SubTexture2D& getSubTexture(const std::string name) const;

		unsigned int getWidth() const { return m_Width; }

		unsigned int getHeight() const { return m_height; }

		void bind() const;

		friend void swap(Texture2D& texture2D1, Texture2D& texture2D2) noexcept
		{
			std::swap(texture2D1.m_ID, texture2D2.m_ID);
			std::swap(texture2D1.m_mode, texture2D2.m_mode);
			std::swap(texture2D1.m_Width, texture2D2.m_Width);
			std::swap(texture2D1.m_height, texture2D2.m_height);
		}
	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_Width;
		unsigned int m_height;

		std::map<std::string, SubTexture2D> m_SubTexture2D;
	};
}