#ifndef _VAO_HPP_
#define _VAO_HPP_
#include <vector>
#include <glm/glm.hpp>

namespace RendererEngine
{
    class VAO
    {
    public:
        VAO();
        ~VAO();
        void Init();
        void Bind();
        unsigned int AddVertexBufferObject(const std::vector<glm::vec3>& data);
        unsigned int AddVertexBufferObject(const std::vector<glm::vec2>& data);
        void AddVertexBufferSubObject(const std::vector<glm::vec2>& data, unsigned int vbo);
        void AddIndices(const std::vector<unsigned int>& data);
        void Draw(unsigned int type);

        VAO(const VAO&) = delete; 
        VAO(VAO&&) = delete;
        VAO& operator=(const VAO&) = delete;
        VAO& operator=(VAO&&) = delete; 
    private:
        unsigned int m_vao;
        std::vector<unsigned int> m_buffers;
        unsigned int m_indicesBuffer = 0;
        size_t m_indicesCount = 0;
	};
}

#endif

