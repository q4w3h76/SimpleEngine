#include <GL/glew.h>
#include <GL/gl.h>
#include "Window.hpp"
#include <stdexcept>
#include "../Game/Game.hpp"

static Game* game;

Window::Window(const std::string title, const unsigned int width, const unsigned int height)
	: m_title(title), m_width(width), m_height(height) {}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
	delete game;
}

void Window::Init()
{
	if(!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");
	mWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	glfwSetWindowSizeLimits(m_window, m_width, m_height, m_width, m_height);
	glfwSetWindowPos(m_window, 700.0f, 150.0f);

	if(!m_window)
		throw std::runtime_error("Failed create window");
	glfwMakeContextCurrent(m_window);
	glewExperimental = true;
	if(glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW");
	game = new Game();
}

void Window::Loop()
{
	glfwSetKeyCallback(m_window, KeyCallback);

	double lastTime = glfwGetTime();
	while(!glfwWindowShouldClose(m_window))
	{
		double nowTime = glfwGetTime();
		double deltaTime = (nowTime - lastTime)*1000;
		if(deltaTime > 10.0f)
		{
			lastTime = nowTime;
			game->Update(deltaTime);
		}
	
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game->Renderer();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	game->Callback(key, action);
}
