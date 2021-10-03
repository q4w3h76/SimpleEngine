#include "Game.hpp"
#include "../RendererEngine/Texture2D.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../Object/Player.hpp"
#include <stdexcept>
#include <fstream>
#include <iterator>

// public method
Game::Game() : m_atlasTexture(new RendererEngine::Texture2D("atlas.png")),
	m_shader(new RendererEngine::ShaderProgram("shader")),
	m_player(new Player(m_atlasTexture, m_shader))
{
	m_atlasTexture->LoadTextureAtlas(std::vector<std::string>{ "playerStopTop", "playerStopBottom",
		"playerStopRight", "playerStopLeft", "playerRunTop", "playerRunBottom", "playerRunRight", "playerRunLeft",
		"smokeFirst", "smokeSecond" }, 25, 25);
}

Game::~Game()
{
	delete m_shader;
	delete m_atlasTexture;
	delete m_player;
}

void Game::Renderer()
{
	m_player->Renderer();
}

void Game::Update(const double delta)
{
	m_player->Update(delta);
}

void Game::Callback(int key, int action)
{
	m_player->Control(key);
}
