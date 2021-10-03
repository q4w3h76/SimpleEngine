#include <GLFW/glfw3.h>
#include "Player.hpp"
#include "../PhysicsEngine/Mass.hpp"

Player::Player(RendererEngine::Texture2D* texture, RendererEngine::ShaderProgram* shader)
	: Object(texture, shader, 2000.0f, { 0.0f, 0.0f }, 0.0f, "player")
{
		InsertState("Stop", "Top");
		InsertState("Stop", "Bottom");
		InsertState("Stop", "Right");
		InsertState("Stop", "Left");
		InsertState("Run", "Top");
		InsertState("Run", "Bottom");
		InsertState("Run", "Right");
		InsertState("Run", "Left");
		SetState(m_currentDirection);
}

Player::~Player()
{

}

void Player::Collision()
{

}

void Player::Control(int key)
{
	const float force = 0.1f;
	if(GLFW_KEY_UP == key)
	{
        m_currentDirection = "Top";
        SetState(m_currentDirection);
		m_mass->ApplyForce({ 0.0f, force });
		StartAnimation("Run", 500);
	}
	if(GLFW_KEY_DOWN == key)
	{
        m_currentDirection = "Bottom";
        SetState(m_currentDirection);
		m_mass->ApplyForce({ 0.0f, -force });
		StartAnimation("Run", 500);
	}
	if(GLFW_KEY_RIGHT == key)
	{
        m_currentDirection = "Right";
        SetState(m_currentDirection);
		m_mass->ApplyForce({ force, 0.0f });
		StartAnimation("Run", 500);
	}
	if(GLFW_KEY_LEFT == key)
	{
        m_currentDirection = "Left";
        SetState(m_currentDirection);
		m_mass->ApplyForce({ -force, 0.0f });
		StartAnimation("Run", 500);
	}
}
