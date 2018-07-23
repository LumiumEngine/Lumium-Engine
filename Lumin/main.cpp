	#include <LumiumEngine/System/Window.hpp>
	#include <glad/glad.h>

	int main(int argc, char **argv)
	{
		lumi::Window window;
		if (window.createWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
		{
			gladLoadGLLoader(SDL_GL_GetProcAddress);

			glClearColor(.2f, .4f, .6f, 1.0f);
			GLfloat verticies[] = { -1, -1,  1,
				0,  1,  1,
				1, -1,  1 };
			GLuint vao, vbo;
			glCreateVertexArrays(1, &vao); // vertex array object
			glCreateBuffers(1, &vbo);	// vertex buffer
			glNamedBufferData(vbo, sizeof(verticies), verticies, GL_STATIC_DRAW);
			glEnableVertexArrayAttrib(vao, 0); // vao, index
			glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(GLfloat));
			glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
			glVertexArrayAttribBinding(vao, 0, 0);
			while (window.isOpen())
			{
				SDL_Event event;
				while (window.pollEvents(&event))
				{
					
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