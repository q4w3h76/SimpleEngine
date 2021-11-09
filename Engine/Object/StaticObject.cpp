#include "StaticObject.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../RendererEngine/Texture2D.hpp"

// protected method

void StaticObject::SetState(const std::string& state, const std::string& direction)
{
	m_sprite->SetState(m_initalSubTexture + state + direction);
	m_currentDirection = direction;
	m_currentState = state;
}

void StaticObject::InsertState(const std::string& state, const std::string& direction)
{
	m_sprite->InsertState(m_initalSubTexture + state + direction);
}

bool StaticObject::CheckCollision(const glm::vec2& position)
{
	const float size = 0.2f;
	bool collisionX = m_sprite->GetPosition().x + size >= position.x &&
		position.x + size >= m_sprite->GetPosition().x;
	bool collisionY = m_sprite->GetPosition().y + size >= position.y &&
		position.y + size >= m_sprite->GetPosition().y;
	return collisionX && collisionY;
}

// public method
StaticObject::StaticObject(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
	const float mass, const glm::vec2& position,
	const float rotation, const std::string& initalSubTexture)
	: m_texture(texture), m_shader(shader), m_initalSubTexture(initalSubTexture)
{
	m_sprite = new RendererEngine::AnimatedSprite(m_texture, m_shader, position, m_size,
		rotation, m_initalSubTexture);
}

StaticObject::~StaticObject()
{
	delete m_sprite;
}

void StaticObject::Renderer()
{
	m_sprite->Renderer();
}

void StaticObject::Update(const double delta, const glm::vec2 position)
{
	m_sprite->Update(delta, m_currentState);
	Collision(position);
}

void StaticObject::StartAnimation(const std::string& state, const unsigned int animationLength)
{
	m_sprite->StartAnimation(m_initalSubTexture + state + m_currentDirection,
		m_currentDirection, animationLength);
}

glm::vec2 StaticObject::GetPosition()
{
	return m_sprite->GetPosition();
}

std::string StaticObject::GetDirection()
{
	return m_currentDirection;
}
