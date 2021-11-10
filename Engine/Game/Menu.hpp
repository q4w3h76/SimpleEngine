#ifndef _MENU_HPP_
#define _MENU_HPP_
#include "../RendererEngine/Texture2D.hpp"
#include "../RendererEngine/ShaderProgram.hpp"
#include "../RendererEngine/AnimatedSprite.hpp"
#include "../RendererEngine/Sprite.hpp"
#include <string>

class Menu
{
public:
	Menu();
	~Menu();
	void Control(int key);
private:
	std::string difficulty = "Low";
	RendererEngine::Texture2D* m_texture;
	RendererEngine::ShaderProgram* m_shader;
	RendererEngine::Sprite* m_title;
	RendererEngine::Sprite* m_subTitle;
	RendererEngine::AnimatedSprite* m_low;
	RendererEngine::AnimatedSprite* m_average;
	RendererEngine::AnimatedSprite* m_hard;
};

#endif
