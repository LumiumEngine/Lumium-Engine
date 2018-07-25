#include <glad/glad.h>
#include <glm/glm.hpp>
#include <LumiumEngine/Graphics/Buffers.hpp>
#include <LumiumEngine/Graphics/Vertex.hpp>
#include <LumiumEngine/System/InputManager.hpp>
#include <LumiumEngine/System/Window.hpp>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	lumi::system::Window window;
	if (window.createWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
	{
		gladLoadGLLoader(SDL_GL_GetProcAddress);

		std::vector<lumi::graphics::Vertex> vertices;

		glClearColor(.2f, .4f, .6f, 1.0f);

		glm::vec3 verticies[] = 
		{
			glm::vec3(-1,  1,  1),
			glm::vec3( 1,  1,  1),
			glm::vec3(-1, -1,  1),
			glm::vec3( 1, -1,  1)
		};
		for (int i = 0; i < 4; i++)
		{
			lumi::graphics::Vertex vert;
			vert.Position = verticies[i];
			vertices.push_back(vert);
		}
		lumi::graphics::Buffers buffer;
		buffer.createVertexBuffers(vertices);
		buffer.createElementBuffer({0, 1, 2, 1, 2, 3});

		lumi::system::InputManager iManager;
		SDL_Event event;
		while (window.isOpen())
		{
			while (iManager.getEvent())
			{
				if (iManager.eventTriggered(SDL_QUIT) || iManager.isKeyPressed(SDLK_ESCAPE))
					window.closeWindow();
			}
			glClear(GL_COLOR_BUFFER_BIT);
			buffer.bindBuffers();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			buffer.unbindBuffers();
			window.display();
		}
	}
	return 1;
}