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

namespace PhysicsEngine
{
	class Mass;
}

class Object
{
public:
	Object(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
		const float mass, const glm::vec2& position,
		const float rotation, const std::string& initalSubTexture);
	virtual ~Object();
	void Renderer();
	void Update(const double delta);
	virtual void Collision() = 0;
	virtual void Control(int key) = 0;
	void StartAnimation(const std::string& state, const unsigned int animationLength);
	glm::vec2 GetPosition();
	std::string GetDirection();
protected:
	RendererEngine::AnimatedSprite* m_sprite;
	PhysicsEngine::Mass* m_mass;
	std::string m_initalSubTexture;
	std::string m_currentDirection = "Top";
	std::string m_currentState = "Stop";
	const glm::vec2 m_size = { 0.7f, 0.65f };

	// protected method
	void SetState(const std::string& direction);
	void InsertState(const std::string& state, const std::string& direction);
	bool CheckCollision(const glm::vec2& position);
private:
	RendererEngine::Texture2D* m_texture;
	RendererEngine::ShaderProgram* m_shader;
};

#endif
