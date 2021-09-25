cmake_minimum_required (VERSION 3.8)
project ("Engine")

add_executable (Engine "main.cpp" "Window/Window.cpp" "Window/Window.hpp"
	"RendererEngine/VAO.cpp" "RendererEngine/VAO.hpp"
	"RendererEngine/ShaderProgram.cpp" "RendererEngine/ShaderProgram.hpp"
	"RendererEngine/Texture2D.cpp" "RendererEngine/Texture2D.hpp"
	"RendererEngine/Sprite.hpp" "RendererEngine/Sprite.cpp"
	"RendererEngine/AnimatedSprite.cpp" "RendererEngine/AnimatedSprite.hpp"
	"PhysicsEngine/Mass.cpp" "PhysicsEngine/Mass.hpp"
	"Game/Game.cpp" "Game/Game.hpp"
	"Object/Object.cpp" "Object/Object.hpp")

target_link_libraries (Engine glfw libglew_static)
