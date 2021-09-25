#include <GL/glew.h>
#include <GL/gl.h>
#include "VAO.hpp"

namespace RendererEngine
{
	VAO::VAO() : m_vao(0) {}

	VAO::~VAO()
	{
		glDeleteBuffers(m_buffers.size(), m_buffers.data());
		glDeleteBuffers(1, &m_indicesBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}

	void VAO::Init()
	{
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
	}

	void VAO::Bind()
	{
		glBindVertexArray(m_vao);
	}

	unsigned int VAO::AddVertexBufferObject(const std::vector<glm::vec3>& data)
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(m_buffers.size(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		m_buffers.push_back(vbo);
		return vbo;
	}

	unsigned int VAO::AddVertexBufferObject(const std::vector<glm::vec2>& data)
	{
		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(m_buffers.size(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		m_buffers.push_back(vbo);
		return vbo;
	}

	void VAO::AddVertexBufferSubObject(const std::vector<glm::vec2>& data, unsigned int vbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(glm::vec2), data.data());
	}

	void VAO::AddIndices(const std::vector<unsigned int>& data)
	{
		assert(m_indicesBuffer == 0);
		m_indicesCount = data.size();
		glGenBuffers(1, &m_indicesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int),
				data.data(), GL_STATIC_DRAW);
	}

	void VAO::Draw(unsigned int type)
	{
		assert(m_indicesBuffer != 0);

		glBindVertexArray(m_vao);
		for(size_t i = 0; i < m_buffers.size(); ++i)
			glEnableVertexAttribArray(i);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
		glDrawElements(type, m_indicesCount, GL_UNSIGNED_INT, nullptr);
		for(size_t i = 0; i < m_buffers.size(); ++i)
			glDisableVertexAttribArray(i);
	}
}
