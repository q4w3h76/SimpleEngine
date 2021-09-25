#include "AnimatedSprite.hpp"
#include "Texture2D.hpp"
#include <iostream> // for std::cerr in function SetState

namespace RendererEngine
{
	AnimatedSprite::AnimatedSprite(Texture2D* texture, ShaderProgram* shader,
		const glm::vec2& position,
		const glm::vec2& size, const float rotation,
		const std::string& initalSubTexture)
		: Sprite(texture, shader, position, size, rotation, initalSubTexture),
		m_initalSubTexture(initalSubTexture)
	{
		m_currentAnimation = m_states.end();
	}


	void AnimatedSprite::InsertState(std::string states)
	{
		m_states.push_back(std::move(states));
	}

	void AnimatedSprite::Renderer()
	{
		if (m_dirty)
		{
			Texture2D::SubTexture SubTexture =
				m_texture->GetSubTexture(m_currentAnimation[m_currentFrame]);
			m_vao.AddVertexBufferSubObject({
				SubTexture.m_rightTopUV,
				{ SubTexture.m_leftBottomUV.x, SubTexture.m_rightTopUV.y },
				SubTexture.m_leftBottomUV,
				{ SubTexture.m_rightTopUV.x, SubTexture.m_leftBottomUV.y }
				}, m_textureCoordsVBO);
			m_dirty = false;
		}
		Sprite::Renderer();
	}

	void AnimatedSprite::Update(const double delta)
	{
		if(m_auxilirayDelta != 0)
			if(m_auxilirayDelta >= m_animationLength)
			{
				m_auxilirayDelta = 0;
				SetState(m_initalSubTexture + "Default");
			}
			else
				m_auxilirayDelta += delta;
	}

	void AnimatedSprite::StartAnimation(const std::string& state, const unsigned int aniLen)
	{
		m_animationLength = aniLen;
		SetState(state);
		m_auxilirayDelta += 1;
	}

	void AnimatedSprite::SetState(const std::string& state)
	{
		std::vector<std::string>::const_iterator it;
		for(it = m_states.begin(); it != m_states.end(); ++it)
			if(*it == state)
				break;
		if (it == m_states.end())
		{
			std::cerr << "Can't find animation state " << state << std::endl;
			return;
		}
		if (it != m_currentAnimation)
		{
			m_currentFrame = 0;
			m_currentAnimation = it;
			m_dirty = true;
		}

	}
}
