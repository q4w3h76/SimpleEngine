#ifndef _STAR_HPP_
#define _STAR_HPP_
#include "StaticObject.hpp"

class Star : public StaticObject
{
public:
	Star(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader);
	void Collision(const glm::vec2 position) override; // will perform the method of starting animation
	void Update(const double delta, const glm::vec2 position) override;
	unsigned int m_score = 0;
};

#endif