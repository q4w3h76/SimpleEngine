#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include <string>
#include <glm/glm.hpp>

namespace RendererEngine
{
	class Texture2D;
	class ShaderProgram;
	class AnimatedSprite;
}

class Object
{
public:
	Object(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
		const glm::vec2& position, const float rotation,
		const std::string& initalSubTexture);
	virtual ~Object();
	void Renderer();
	void Update(const double delta);
	virtual unsigned int Attack() = 0; //return damage
	virtual void Move(const glm::vec2& position) = 0;
	void StartAnimation(const std::string& state, const unsigned int animationLength);
protected:
	RendererEngine::AnimatedSprite* m_sprite;
	std::string m_initalSubTexture;
	const glm::vec2 m_size = { 0.7f, 0.65f };

	// protected method
	void SetState(const std::string& state);
	void InsertState(const std::string& state);
private:
	RendererEngine::Texture2D* m_texture;
	RendererEngine::ShaderProgram* m_shader;
};

#endif
