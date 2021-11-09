#include "Star.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"

Star::Star(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader)
	: StaticObject(texture, shader, 2000.0f, { 0.0f, 0.0f }, 0.0f, "star")
{
	InsertState("First", "");
	InsertState("Second", "");
	SetState("First", "");
}

void Star::Collision(const glm::vec2 position)
{
	if (CheckCollision(position))
	{
		++m_score;

		m_sprite->SetPosition({ 1.0, 0.0 });
	}
}

void Star::Update(const double delta, const glm::vec2 position)
{
	if(m_currentState == "First")
		SetState("Second", "");
	else
		SetState("First", "");
	StaticObject::Update(delta, position);
}