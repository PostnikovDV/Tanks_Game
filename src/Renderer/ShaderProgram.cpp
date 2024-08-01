#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertexShader, std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile-time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint succes;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint succes;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) noexcept
	{
		ShaderProgram tmp(std::move(shaderProgram));
		swap(*this, shaderProgram);
		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		swap(*this, shaderProgram);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}
}

