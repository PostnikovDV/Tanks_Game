#include "Texture2D.h"

namespace RenderEngine
{
	Texture2D::Texture2D(const GLuint widht, const GLuint height,
		const unsigned char* data,
		const unsigned int channels,
		const GLenum filter,
		const GLenum wrapMode): m_widht(widht), m_height(height)
	{
		switch (channels)
		{
		case 4:
			m_mode = GL_RGBA;
			break;
		case 3:
			m_mode = GL_RGB;
			break;
		default:
			m_mode = GL_RGBA;
			break;
		}

		glGenTextures(1, &m_ID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_mode, widht, height, 0, m_mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(Texture2D&& texture2D) noexcept
	{
		swap(*this, texture2D);
	}
	Texture2D& Texture2D::operator = (Texture2D&& texture2D) noexcept
	{
		Texture2D tmp(std::move(texture2D));
		swap(*this, tmp);
		return *this;
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::addSubTexture2D(std::string name, glm::vec2& leftBottomUV, glm::vec2& rightTopUV)
	{
		m_SubTexture2D.emplace(std::move(name), SubTexture2D(leftBottomUV, rightTopUV));
	}

	const Texture2D::SubTexture2D& Texture2D::getSubTexture(const std::string name) const
	{
		auto it = m_SubTexture2D.find(name);
		
		if (it != m_SubTexture2D.end())
			return it->second;

		const static SubTexture2D defaultSubTexture;
		return defaultSubTexture;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}