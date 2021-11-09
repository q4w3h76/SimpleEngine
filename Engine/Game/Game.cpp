#include "Game.hpp"
#include "../RendererEngine/Texture2D.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../Object/Player.hpp"
#include "../Object/Star.hpp"
#include <stdexcept>
#include <fstream>
#include <iterator>

// public method
Game::Game() : m_atlasTexture(new RendererEngine::Texture2D("atlas.png")),
	m_shader(new RendererEngine::ShaderProgram("shader")),
	m_player(new Player(m_atlasTexture, m_shader)),
	m_star(new Star(m_atlasTexture, m_shader))
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
}

void Game::Renderer()
{
	m_player->Renderer();
	m_star->Renderer();
}

void Game::Update(const double delta)
{
	m_player->Update(delta);
	m_star->Update(delta, m_player->GetPosition());
}

void Game::Callback(int key, int action)
{
	m_player->Control(key);
}
