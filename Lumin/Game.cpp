#include "Game.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include <LumiumEngine/Graphics/Shapes/Cube.hpp>

Game::Game()
{

}

Game::~Game()
{

}

void Game::start()
{
	if (m_window.createWindow("Lumin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
	{
		gladLoadGLLoader(SDL_GL_GetProcAddress); // load OpenGL
		auto size = m_window.getSize();
		glViewport(0, 0, size.x, size.y);
		m_camera.setPerspective(45.0f, size.x / size.y, .1f, -100.0f);
		setup();
	}
}

void Game::setup()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	m_drawables.push_back(std::make_unique<lumi::graphics::Cube>());
	auto cube = dynamic_cast<lumi::graphics::Cube*>(m_drawables.back().get());
	cube->createCube(glm::vec3(1));
	m_buffers.createVertexBuffers(cube->getVertices());
	m_buffers.createElementBuffer(cube->getIndices());
	
	m_shaders.addShader("Shaders/cube.vert", GL_VERTEX_SHADER);
	m_shaders.addShader("Shaders/cube.frag", GL_FRAGMENT_SHADER);
	m_shaders.compileProgram();

	auto loaded = m_font.loadFont("Fonts/arial.ttf");
	
	m_texture.createTexture("Images/test.png");
	
	m_camera.setCameraCenter(glm::vec3(0, 0, 0));
	m_camera.setCameraPosition(glm::vec3(0, 0, -2));

	glClearColor(.1f, .8f, .2f, 1.0f);
	run();
}

void Game::run()
{
	m_Timer.startTime();
	m_Timer.setTimeStep(60);
	while (m_window.isOpen())
	{
		m_Timer.sleepCycle();
		update(m_Timer.getFrameTime());
		processInput();
		display();
	}
}

void Game::processInput()
{
	while (m_eventManager.getEvent())
	{
		if (m_eventManager.isKeyPressed(SDLK_f))
		{
			m_window.toggleFullScreen();
		}
		if (m_eventManager.eventTriggered(SDL_QUIT) || m_eventManager.isKeyPressed(SDLK_ESCAPE))
		{
			m_window.closeWindow();
		}
		if (m_eventManager.eventTriggered(SDL_WINDOWEVENT))
		{
			if (m_eventManager.isWindowEvent(SDL_WINDOWEVENT_RESIZED) || m_eventManager.isWindowEvent(SDL_WINDOWEVENT_SIZE_CHANGED))
			{
				glm::vec2 size = m_eventManager.getWindowSize();
				if (size.x > 0 && size.y > 0)
				{
					glViewport(0, 0, size.x, size.y);
					m_camera.setPerspective(45.0f, size.x / size.y, 0.1f, 100.0f);
				}
			}
		}
	}
	m_eventManager.getKeyboardState();
	m_eventManager.getMouseState();
}

void Game::update(float time)
{
	float radius = 5.0f;
	auto elTime = m_Timer.getElapsedTime();
	float camX = std::sin(elTime) * radius;
	float camZ = std::cos(elTime) * radius;
	m_camera.setCameraPosition(glm::vec3(camX, 0, camZ));

	auto & model = dynamic_cast<lumi::graphics::Cube*>(m_drawables.back().get())->getModel();
	static int test;
	if (!test)
		model = glm::scale(model, glm::vec3(.5));
	test++;
	m_shaders.useProgram();
	m_shaders.glUniformMatrix(m_shaders.getUniformLocation("Model"), GL_FALSE, m_camera.getProj() * m_camera.getView() * model);
	m_shaders.unuseProgram();
}

void Game::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_buffers.bindBuffers();
	m_texture.bindTexture();
	m_shaders.useProgram();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
	m_texture.unbindTexture();
	m_shaders.unuseProgram();
	m_buffers.unbindBuffers();
	m_window.display();
}
