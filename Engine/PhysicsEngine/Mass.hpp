#ifndef _MASS_HPP_
#define _MASS_HPP_
#include <glm/glm.hpp>

namespace PhysicsEngine {
	class Mass
	{
	protected:
		float m_mass;
		glm::vec2 m_position,
			m_acceleration, m_force;
		uint64_t m_time;
	public:
		Mass(const float mass = 0.1f, const glm::vec2& position = glm::vec2(0.0f, 0.0f));
		~Mass() = default;
		void Init();
		void ApplyForce(const glm::vec2& force);
		void Simulate(const float delta);
		void Stop();
		void Reaction();
		glm::vec2 GetPosition() const;
		glm::vec2 GetForce() const;
		glm::vec2 GetAcceleration() const;
		void SetAcceleration(const glm::vec2 acceleration);
		void SetPosition(const glm::vec2& pos);
		void SetForce(const glm::vec2& force);
	};
}

#endif
