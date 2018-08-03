#include <glad/glad.h>
#include <glm/glm.hpp>
#include <LumiumEngine/Graphics/Buffers.hpp>
#include <LumiumEngine/Graphics/Texture.hpp>
#include <LumiumEngine/Graphics/Vertex.hpp>
#include <LumiumEngine/System/InputManager.hpp>
#include <LumiumEngine/System/Shaders.hpp>
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

		glClearColor(.2f, 0.2f, .2f, 1.0f);

		glm::vec3 verticies[] = 
		{
			glm::vec3(-0.5,  0.5,  1),
			glm::vec3( 0.5,  0.5,  1),
			glm::vec3(-0.5, -0.5,  1),
			glm::vec3( 0.5, -0.5,  1)
		};

		glm::vec2 uvs[] =
		{
			glm::vec2(0, 1),	// top left
			glm::vec2(1, 1),	// top right
			glm::vec2(0, 0),	// bottom left
			glm::vec2(1, 0)		// bottom right
		};

		for (int i = 0; i < 4; i++)
		{
			lumi::graphics::Vertex vert;
			vert.Position = verticies[i];
			vert.TexCoord = uvs[i];
			vertices.push_back(vert);
		}
		lumi::graphics::Buffers buffer;
		buffer.createVertexBuffers(vertices);
		buffer.createElementBuffer({0, 1, 2, 1, 2, 3});

		lumi::system::Shaders shaders;
		shaders.addShader("Shaders/test.vert", GL_VERTEX_SHADER);
		shaders.addShader("Shaders/test.frag", GL_FRAGMENT_SHADER);
		shaders.compileProgram();

		lumi::graphics::Texture texture;
		int texCount = texture.createTextureArray("Images/test.png", 128, 128);
		int currentIndex = 0;

		lumi::system::InputManager iManager;
		SDL_Event event;
		while (window.isOpen())
		{
			while (iManager.getEvent())
			{
				if (iManager.eventTriggered(SDL_QUIT) || iManager.isKeyPressed(SDLK_ESCAPE))
					window.closeWindow();
			}
			texture.bindTexture();
			shaders.useProgram();
			shaders.glUniform(shaders.getUniformLocation("imageIndex"), currentIndex);

			// draw stuff
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			buffer.bindBuffers();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			buffer.unbindBuffers();
			shaders.unuseProgram();
			window.display();
			// end draw

			currentIndex++;
			if (currentIndex > texCount)
				currentIndex = 0;
		}
	}
	return 1;
}