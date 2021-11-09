#ifndef _ANIMATED_SPRITE_HPP_
#define _ANIMATED_SPRITE_HPP_
#include "Sprite.hpp"

namespace RendererEngine
{
	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(Texture2D* texture, ShaderProgram* shader,
			const glm::vec2& position = glm::vec2(0.0f, 0.0f),
			const glm::vec2& size = glm::vec2(1.0f, 1.0f),
			const float rotation = 0.0f, const std::string& initalSubTexture = "default");
		~AnimatedSprite() = default;
		void InsertState(std::string state);
		void Renderer() override;
		void Update(const double delta, const std::string& state);
		void StartAnimation(const std::string& state,
                            const std::string& direction, const unsigned int aniLen);
		void SetState(const std::string& state);
		glm::vec2 GetPosition();
	private:
		std::vector<std::string> m_states;
		std::string m_lastDirection;
		size_t m_currentFrame = 0;
		std::vector<std::string>::const_iterator m_currentAnimation;
		std::string m_initalSubTexture;
		bool m_dirty = false;
		unsigned int m_auxilirayDelta = 0, m_animationLength = 0;
	};
}

#endif
