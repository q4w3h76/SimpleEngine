#ifndef _GAME_HPP_
#define _GAME_HPP_
#include <glm/glm.hpp>
#include <string>

namespace RendererEngine
{
	class Texture2D;
	class ShaderProgram;
}

class Player;
class Star;

class Game
{
public:
	Game();
	~Game();
	void Renderer();
	void Update(const double delta);
	void Callback(int key, int action);
private:
	RendererEngine::Texture2D* m_atlasTexture;
	RendererEngine::ShaderProgram* m_shader;
	Player* m_player;
	Star* m_star;
};

#endif
