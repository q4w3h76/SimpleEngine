#include "Mass.hpp"

namespace PhysicsEngine {

	Mass::Mass(const float mass, const glm::vec2& position)
		: m_acceleration(0.0f, 0.0f), m_position(position), m_mass(mass){}

	void Mass::Init()
	{
		m_force.x = 0.0f;
		m_force.y = 0.0f;
	}

	void Mass::ApplyForce(const glm::vec2& force)
	{
		m_force += force;
	}
	
	void Mass::Simulate(const float delta)
	{
		const float frictionForce = 0.00003f;
		m_acceleration += (m_force / m_mass) * delta;

		if (m_acceleration.x > 0)
			m_acceleration.x -= frictionForce;
		if (m_acceleration.x < 0)
			m_acceleration.x += frictionForce;
		if (m_acceleration.y > 0)
			m_acceleration.y -= frictionForce;
		if (m_acceleration.y < 0)
			m_acceleration.y += frictionForce;
	
		m_position += m_acceleration * delta;
	}

	void Mass::Stop()
	{
		m_acceleration *= glm::vec2(0.0f, 0.0f);
	}

	void Mass::Reaction()
	{
		m_acceleration *= glm::vec2(-1.0f, -1.0f);
	}

	glm::vec2 Mass::GetPosition() const
	{
		return m_position;
	}

	glm::vec2 Mass::GetForce() const
	{
		return m_force;
	}

	glm::vec2 Mass::GetAcceleration() const
	{
		return m_acceleration;
	}

	void Mass::SetAcceleration(const glm::vec2 acceleration)
	{
		m_acceleration = acceleration;
	}

	void Mass::SetPosition(const glm::vec2& position)
	{
		m_position = position;
	}

	void Mass::SetForce(const glm::vec2& force)
	{
		m_force = force;
	}
}
