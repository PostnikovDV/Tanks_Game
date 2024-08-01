#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class ShaderProgram 
	{
	public:
		ShaderProgram(const std::string& vertexShader, std::string& fragmentShader);
		~ShaderProgram();

		bool isCompiled() const 
		{
			return m_isCompiled;
		}

		friend void swap(ShaderProgram& shader1, ShaderProgram& shader2) noexcept
		{
			std::swap(shader1.m_isCompiled, shader2.m_isCompiled);
			std::swap(shader1.m_ID, shader2.m_ID);
		}
		

		void use() const;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&&) noexcept;
		ShaderProgram& operator = (ShaderProgram&&) noexcept;
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled{ false }; //��� �������� ���������� � �������� ��������
		GLuint m_ID{ 0 }; //������������� ��������� ���������

	};
}