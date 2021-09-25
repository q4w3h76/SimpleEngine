#include "Game.hpp"
#include "../RendererEngine/Texture2D.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <fstream>
#include <iterator>

// public method
Game::Game() : m_atlasTexture(new RendererEngine::Texture2D("atlas.png")),
	m_shader(new RendererEngine::ShaderProgram("shader")),
	sprite(new RendererEngine::AnimatedSprite(m_atlasTexture, m_shader, { 0.0f, 0.0f }, { 1.0, 1.0 }, 0.0f, "first"))
{
	m_atlasTexture->LoadTextureAtlas(std::vector<std::string>{ "first", "second" }, 8, 8);
	sprite->InsertState("first");
	sprite->InsertState("second");
	sprite->SetState("first");
}

Game::~Game()
{
	delete m_shader;
	delete m_atlasTexture;
	delete sprite;
}

void Game::Renderer()
{
	sprite->Renderer();
}

void Game::Update(const double delta)
{
	sprite->Update(delta);
}

void Game::Callback(int key, int action)
{
	if(key == GLFW_KEY_SPACE)
		sprite->StartAnimation("second", 10000);
}
