#include "Game.hpp"
#include "../RendererEngine/Texture2D.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../Object/Player.hpp"
#include "../Object/Star.hpp"
#include "../Object/Meteorite.hpp"
#include <stdexcept>
#include <fstream>
#include <iterator>
#include <iostream>

// public method
Game::Game(const float speed) : m_atlasTexture(new RendererEngine::Texture2D("atlas.png")),
	m_shader(new RendererEngine::ShaderProgram("shader")),
	m_player(new Player(m_atlasTexture, m_shader)),
	m_star(new Star(m_atlasTexture, m_shader)),
	m_meteorite(new Meteorite(m_atlasTexture, m_shader, speed))
{
	m_atlasTexture->LoadTextureAtlas(std::vector<std::string>{ "playerStopTop", "playerStopBottom",
		"playerStopLeft", "playerStopRight", "playerRunTop", "playerRunBottom", "playerRunLeft", "playerRunRight",
		"starFirst", "starSecond", "Meteorite" }, 25, 25);
}

Game::~Game()
{
	delete m_shader;
	delete m_atlasTexture;
	delete m_player;
	delete m_star;
	delete m_meteorite;
}

void Game::Renderer()
{
	m_player->Renderer();
	m_star->Renderer();
	m_meteorite->Renderer();
}

void Game::Update(const double delta)
{
	m_player->Update(delta);
	m_star->Update(delta, m_player->GetPosition());
	m_meteorite->Update(delta);
	if (CheckCollision(m_player->GetPosition(), m_meteorite->GetPosition()))
	{
		std::cout << m_star->m_score << std::endl << "Good game!" << std::endl;
		std::cout << "Reolading the game" << std::endl;
		m_player->SetPosition({ 0.0f, 0.0f });
		m_meteorite->SetPosition({ 3.6f, 0.0f });
		m_star->m_score = 0;
	}
}

void Game::Callback(int key, int action)
{
	m_player->Control(key);
}

// private method
bool Game::CheckCollision(const glm::vec2& position1, const glm::vec2& position2)
{
	const float size = 0.2f;
	bool collisionX = position1.x + size >= position2.x &&
		position2.x + size >= position1.x;
	bool collisionY = position1.y + size >= position2.y &&
		position2.y + size >= position1.y;
	return collisionX && collisionY;
}