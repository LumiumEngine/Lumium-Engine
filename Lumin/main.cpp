	#include <LumiumEngine/System/Window.hpp>
	#include <glad/glad.h>

	int main(int argc, char **argv)
	{
		lumi::Window window;
		if (window.createWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
		{
			gladLoadGLLoader(SDL_GL_GetProcAddress);
			glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
			while (window.isOpen())
			{
				glClear(GL_COLOR_BUFFER_BIT);
				window.display();
			}
		}
		return 1;
	}