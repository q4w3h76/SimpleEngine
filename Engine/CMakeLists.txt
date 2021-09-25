cmake_minimum_required (VERSION 3.8)
project ("Engine")

add_executable (Engine "src/main.cpp" "src/Window/Window.cpp" "src/Window/Window.hpp"
	"src/RendererEngine/VAO.cpp" "src/RendererEngine/VAO.hpp"
	"src/RendererEngine/ShaderProgram.cpp" "src/RendererEngine/ShaderProgram.hpp"
	"src/RendererEngine/Texture2D.cpp" "src/RendererEngine/Texture2D.hpp"
	"src/RendererEngine/Sprite.hpp" "src/RendererEngine/Sprite.cpp"
	"src/RendererEngine/AnimatedSprite.cpp" "src/RendererEngine/AnimatedSprite.hpp"
	"src/PhysicsEngine/Mass.cpp" "src/PhysicsEngine/Mass.hpp"
	"src/Object/Object.cpp" "src/Object/Object.hpp")

target_link_libraries (Engine glfw libglew_static)
