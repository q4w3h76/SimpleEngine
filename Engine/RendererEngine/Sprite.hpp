#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_
#include "VAO.hpp"
#include <glm/glm.hpp>
#include <string>

namespace RendererEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		Sprite(Texture2D* texture, ShaderProgram* shader,
                        const glm::vec2& position = glm::vec2(0.0f, 0.0f),
                        const glm::vec2& size = glm::vec2(1.0f, 1.0f),
                        const float rotation = 0.0f,
                        const std::string& initalSubTexture = "default");
		~Sprite() = default;

		virtual void Renderer();
		void SetPosition(const glm::vec2& position);
	protected:
		Texture2D* m_texture;
		ShaderProgram* m_shader;
		VAO m_vao;
		unsigned int m_vertexCoordsVBO;
		unsigned int m_textureCoordsVBO;
	private:
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
	};
}

#endif
