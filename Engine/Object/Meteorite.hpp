#ifndef _METEORITE_HPP_
#define _METEORITE_HPP_
#include "Object.hpp"

class Meteorite : public Object
{
public:
	Meteorite(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader, const float speed);
	void Collision() override;
	void Control(int key) override;// not use
private:
	float m_speed;
};

#endif