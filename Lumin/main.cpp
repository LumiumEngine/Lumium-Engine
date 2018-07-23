#include <LumiumEngine/Graphics/Vertex.hpp>
#include <LumiumEngine/System/Window.hpp>
#include <LumiumEngine/System/InputManager.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>

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
			glm::vec3(-1, -1,  1),
			glm::vec3( 0,  1,  1),
			glm::vec3( 1, -1,  1) 
		};
		for (int i = 0; i < 3; i++)
		{
			lumi::graphics::Vertex vert;
			vert.Position = verticies[i];
			vertices.push_back(vert);
		}
		GLuint vao, vbo;
		glCreateVertexArrays(1, &vao); // vertex array object

		glCreateBuffers(1, &vbo);	// vertex buffer
		glNamedBufferStorage(vbo, vertices.size() * sizeof(lumi::graphics::Vertex), vertices.data(), GL_DYNAMIC_STORAGE_BIT);
		
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(lumi::graphics::Vertex));

		glEnableVertexArrayAttrib(vao, 0); // vao, index

		glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(lumi::graphics::Vertex, Position));
		
		glVertexArrayAttribBinding(vao, 0, 0);

		lumi::system::InputManager iManager;
		SDL_Event event;
		while (window.isOpen())
		{
			while (iManager.getEvent())
			{
				if (iManager.isKeyPressed(SDLK_ESCAPE))
					window.closeWindow();
			}
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			window.display();
		}
	}
	return 1;
}