#include <GL/glew.h>
#include <GL/gl.h>
#include "ShaderProgram.hpp"
#include <iostream>
#include <iterator>
#include <fstream>

namespace RendererEngine
{
	// public method
	ShaderProgram::ShaderProgram(const std::string& name)
	{
		m_program = glCreateProgram();
		m_vertexShader = CompileShader("../../resources/GLSL/" + name + ".vert", GL_VERTEX_SHADER);
		m_fragmentShader = CompileShader("../../resources/GLSL/" + name + ".frag", GL_FRAGMENT_SHADER);
	}

	ShaderProgram::ShaderProgram(const ShaderProgram& shader)
	{
		m_program = shader.m_program;
		m_fragmentShader = shader.m_fragmentShader;
		m_vertexShader = shader.m_vertexShader;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDetachShader(m_program, m_vertexShader);
		glDetachShader(m_program, m_fragmentShader);
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);
		glDeleteProgram(m_program);
	}

	void ShaderProgram::Link()
	{
		glAttachShader(m_program, m_vertexShader);
		glAttachShader(m_program, m_fragmentShader);

		glLinkProgram(m_program);
	}

	void ShaderProgram::Use()
	{
		glUseProgram(m_program);
	}

	void ShaderProgram::BindAttribute(const unsigned int index, const std::string& name)
	{
		glBindAttribLocation(m_program, index, name.c_str());
	}

	void ShaderProgram::Uniform1i(const std::string& name, int a)
	{
		unsigned int u_loc = glGetUniformLocation(m_program, name.c_str());
		glUniform1i(u_loc, a);
	}

	void ShaderProgram::Uniform4f(const std::string& name, float a, float b, float c, float d)
	{
		unsigned int u_loc = glGetUniformLocation(m_program, name.c_str());
		glUniform4f(u_loc, a, b, c, d);
	}

	void ShaderProgram::UniformMatrix4f(const std::string& name, glm::mat4 transform)
	{
		unsigned int u_loc = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix4fv(u_loc, 1, GL_FALSE, &transform[0][0]);
	}

	// private method
	unsigned int ShaderProgram::CompileShader(const std::string& path, unsigned int typeShader)
	{
		unsigned int shader = glCreateShader(typeShader);
		std::ifstream ifstream(path);
		std::string shaderCode = { std::istreambuf_iterator<char>(ifstream),
						std::istreambuf_iterator<char>() };
		const char* str = shaderCode.c_str();
                glShaderSource(shader, 1, &str, nullptr);

                glCompileShader(shader);

                int status;
                glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
                char buf[4096];
                int len;
                glGetShaderInfoLog(shader, sizeof(buf), &len, buf);
                if (len > 0)
                        std::cerr << path << ":" << std::endl << buf;
                if (!status)
                        throw std::runtime_error("failed to compile shader " + path);
                return shader;
	}
}
