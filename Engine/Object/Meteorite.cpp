#include "Meteorite.hpp"
#include "../PhysicsEngine/Mass.hpp"
#include <cstdlib>
#include <ctime>

Meteorite::Meteorite(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader, const float speed)
	: Object(texture, shader, 4000.0f, { 3.6f, 0.0f }, 0.0f, "Meteorite", ""), m_speed(speed)
{
	InsertState("", "");
	SetState("");
	m_mass->ApplyForce({ -m_speed, 0.0f });
	srand(time(0));
}


void Meteorite::Collision()
{
	m_mass->SetForce({ -m_speed, 0.0f });
	m_mass->SetAcceleration({ 0.0f, 0.0f });
	if (GetPosition().x < -3.6)
	{
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.2f - 0.0f)));
		unsigned int signY = rand() % 2;
		if (signY == 0)
			y *= -1;
		m_mass->SetPosition({ 3.6f, y });
	}
}

void Meteorite::Control(int key)
{

}