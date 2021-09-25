#ifndef _SHADER_PROGRAM_HPP_
#define _SHADER_PROGRAM_HPP_
#include <string>
#include <glm/glm.hpp>

namespace RendererEngine
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& name);
		ShaderProgram(const ShaderProgram& shader);
		~ShaderProgram();
		void Link();
		void Use();
		void BindAttribute(const unsigned int index, const std::string& name);
		void Uniform1i(const std::string& name, int a);
		void Uniform4f(const std::string& name, float a, float b, float c, float d);
		void UniformMatrix4f(const std::string& name, glm::mat4 transform);	
	private:
		unsigned int m_program, m_vertexShader, m_fragmentShader;

		unsigned int CompileShader(const std::string& path, unsigned int typeShader);
	};
}

#endif
