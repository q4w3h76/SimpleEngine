#include "Window/Window.hpp"
#include <iostream>

int main()
{
	Window* window = new Window("Engine", 800, 600);
	try
	{
		window->Init();
		window->Loop();
	}
	catch(std::runtime_error error)
	{
		std::cerr << "EXCEPTION: " << error.what() << std::endl;
		delete window;
		return -1;
	}
	delete window;
	return 0;
}
