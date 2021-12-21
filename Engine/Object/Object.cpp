#include "Object.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../RendererEngine/Texture2D.hpp"
#include "../PhysicsEngine/Mass.hpp"

// protected method

void Object::SetState(const std::string& direction)
{
	m_sprite->SetState(m_initalSubTexture + m_currentState + direction);
	m_currentDirection = direction;
}

void Object::InsertState(const std::string& state, const std::string& direction)
{
	m_sprite->InsertState(m_initalSubTexture + state + direction);
}

bool Object::CheckCollision(const glm::vec2& position)
{
	const float size = 0.2f;
	bool collisionX = m_mass->GetPosition().x + size >= position.x &&
	    position.x + size >= m_mass->GetPosition().x;
	bool collisionY = m_mass->GetPosition().y + size >= position.y &&
		position.y + size >= m_mass->GetPosition().y;
	return collisionX && collisionY;
}

// public method
Object::Object(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
		const float mass, const glm::vec2& position,
		const float rotation, const std::string& initalSubTexture, const std::string& startState)
		: m_texture(texture), m_shader(shader), m_initalSubTexture(initalSubTexture), m_currentState(startState)
{
	m_sprite = new RendererEngine::AnimatedSprite(m_texture, m_shader, position, m_size,
							rotation, m_initalSubTexture);
	m_mass = new PhysicsEngine::Mass(mass, position);
	m_mass->Init();
}

Object::~Object()
{
	delete m_sprite;
	delete m_mass;
}

void Object::Renderer()
{
	m_sprite->Renderer();
}

void Object::Update(const double delta)
{
	m_mass->Simulate(delta);
	m_mass->Init();
	m_sprite->SetPosition(m_mass->GetPosition());
	m_sprite->Update(delta, m_currentState);
	Collision();
}

void Object::StartAnimation(const std::string& state, const unsigned int animationLength)
{
	m_sprite->StartAnimation(m_initalSubTexture + state + m_currentDirection,
                             m_currentDirection, animationLength);
}

glm::vec2 Object::GetPosition()
{
	return m_mass->GetPosition();
}

std::string Object::GetDirection()
{
	return m_currentDirection;
}


void Object::SetPosition(glm::vec2 position)
{
	m_mass->SetPosition(position);
	m_mass->SetForce({ 0.0f, 0.0f });
	m_mass->SetAcceleration({ 0.0f, 0.0f });
	m_sprite->SetPosition(position);
}
