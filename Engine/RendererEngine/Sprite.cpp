#include <GL/glew.h>
#include <GL/gl.h>
#include "Sprite.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture2D.hpp"
#include "ShaderProgram.hpp"

namespace RendererEngine
{
	Sprite::Sprite(Texture2D* texture, ShaderProgram* shader,
		const glm::vec2& position,
		const glm::vec2& size, const float rotation,
		const std::string& initalSubTexture)
		: m_texture(texture), m_shader(shader),
		m_position(position), m_size(size), m_rotation(rotation)
	{
		m_vao.Init();
		m_vertexCoordsVBO = m_vao.AddVertexBufferObject({
			{ 0.5f, 0.5f },
			{ -0.5f, 0.5f },
			{ -0.5f, -0.5f },
			{ 0.5f, -0.5f }
			});
		Texture2D::SubTexture SubTexture =
			m_texture->GetSubTexture(std::move(initalSubTexture));
		m_textureCoordsVBO = m_vao.AddVertexBufferObject({
			SubTexture.m_rightTopUV,
			{ SubTexture.m_leftBottomUV.x, SubTexture.m_rightTopUV.y },
			SubTexture.m_leftBottomUV,
			{ SubTexture.m_rightTopUV.x, SubTexture.m_leftBottomUV.y }
			});
		m_vao.AddIndices({ 0, 1, 3, 2, 1, 3 });
		m_shader->Uniform1i("slot", 0);
		m_shader->BindAttribute(0, "position");
		m_shader->BindAttribute(1, "texture");
        m_shader->Link();
	}

	void Sprite::Renderer()
	{
		m_shader->Use();
		glm::mat4 modelMatrix(1.0f);
		modelMatrix = glm::translate(modelMatrix, { m_position, -2.0f });
		modelMatrix = glm::translate(modelMatrix,
			glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation),
			glm::vec3(0.0f, 0.0f, -1.0f));
		modelMatrix = glm::translate(modelMatrix,
			glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(m_size, 0.0f));

		glm::mat4 projectionMatrix = glm::perspective(90.f, (float)(1280 / 720), 1.0f, 100.0f);

		m_shader->UniformMatrix4f("ModelMatrix", modelMatrix);
		m_shader->UniformMatrix4f("ProjectionMatrix", projectionMatrix);
		m_texture->Bind();
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.8f);
		m_vao.Draw(GL_TRIANGLES);
		glDisable(GL_ALPHA_TEST);
	}

	void Sprite::SetPosition(const glm::vec2& position)
	{
		m_position = position;
	}
}
