#ifndef _STATIC_OBJECT_HPP_
#define _STATIC_OBJECT_HPP_
#include <string>
#include <glm/glm.hpp>

namespace RendererEngine
{
	class Texture2D;
	class ShaderProgram;
	class AnimatedSprite;
}

class StaticObject
{
public:
	StaticObject(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
		const float mass, const glm::vec2& position,
		const float rotation, const std::string& initalSubTexture);
	virtual ~StaticObject();
	void Renderer();
	virtual void Update(const double delta, const glm::vec2 position);
	virtual void Collision(const glm::vec2 position) = 0;
	void StartAnimation(const std::string& state, const unsigned int animationLength);
	glm::vec2 GetPosition();
	std::string GetDirection();
protected:
	RendererEngine::AnimatedSprite* m_sprite;
	std::string m_initalSubTexture;
	std::string m_currentDirection = "";
	std::string m_currentState = "";
	const glm::vec2 m_size = { 0.35f, 0.325f };

	// protected method
	void SetState(const std::string& state, const std::string& direction);
	void InsertState(const std::string& state, const std::string& direction);
	bool CheckCollision(const glm::vec2& position);
private:
	RendererEngine::Texture2D* m_texture;
	RendererEngine::ShaderProgram* m_shader;
};

#endif
