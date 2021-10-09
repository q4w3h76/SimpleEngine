#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "Object.hpp"

class Player : public Object
{
public:
	Player(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader);
	~Player();
	void Collision() override;
	void Control(int key) override;
private:
	void CollisionWithBorder();
};

#endif
