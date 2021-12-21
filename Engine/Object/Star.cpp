#include "Star.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include <cstdlib>
#include <ctime>

Star::Star(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader)
	: StaticObject(texture, shader, 2000.0f, { 0.0f, 0.0f }, 0.0f, "star")
{
	InsertState("First", "");
	InsertState("Second", "");
	SetState("First", "");
	srand(time(0));
}

void Star::Collision(const glm::vec2 position)
{
	if (CheckCollision(position))
	{
		++m_score;
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.2f - 0.0f)));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.2f - 0.0f)));
		unsigned int signX = rand() % 2;
		unsigned int signY = rand() % 2;
		if(signX == 0)
			x *= -1;
		if(signY == 0)
			y *= -1;
		m_sprite->SetPosition({ x, y });
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
