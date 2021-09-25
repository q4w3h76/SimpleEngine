#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
	GLFWwindow* m_window;
	std::string m_title;
	unsigned int m_width, m_height;
public:
	Window(const std::string title, const unsigned int width, const unsigned int height);
	~Window();
	void Init();
	void Loop();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
