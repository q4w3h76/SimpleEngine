#include "Object.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../RendererEngine/Texture2D.hpp"

// protected method

void Object::SetState(const std::string& state)
{
	m_sprite->SetState(m_initalSubTexture + state);
}

void Object::InsertState(const std::string& state)
{
	m_sprite->InsertState(m_initalSubTexture + state);
}

// public method
Object::Object(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader,
		const glm::vec2& position, const float rotation,
		const std::string& initalSubTexture)
		: m_texture(texture), m_shader(shader), m_initalSubTexture(initalSubTexture)
{
	mSprite = new RendererEngine::AnimatedSprite(m_texture, m_shader, m_position, m_size,
							rotation, m_initalSubTexture);
}

Object::~Object()
{
	delete m_sprite;
}

void Object::Renderer()
{
	m_sprite->Renderer();
}

void Object::Update(const double delta)
{
	m_sprite->Update(delta);
}

void Object::StartAnimation(const std::string& state, const unsigned int animationLength)
{
	m_sprite->StartAnimation(m_initalSubTexture + state, animationLength);
}

unsigned int Object::GetCoverageArea() const
{
	return coverageArea;
}
