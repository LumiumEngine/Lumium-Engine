#include "Game.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <iostream>
#include <LumiumEngine/Graphics/Shapes/2D/Square.hpp>
#include <LumiumEngine/Graphics/Font.hpp>

Game::Game()
{
	m_cameraZoom = 1.0;
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
		m_camera.setOrtho(0, size.x, 0, size.y, .01f, 10000.0f);
		setup();
	}
}

void Game::setup()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_font = std::make_shared<lumi::graphics::Font>();
	auto loaded = m_font->loadFont("Fonts/arial.ttf");
	if(loaded != 0)
	{
		m_text.setFont(m_font);
		m_text.createText(m_Timer.getCurrentTimeLabel());
	}

	//m_buffers.createVertexBuffers(m_text.getVertices());
	//m_buffers.createElementBuffer(m_text.getIndices());
	
	m_drawables.push_back(std::make_unique<lumi::graphics::Square>());
	auto square = dynamic_cast<lumi::graphics::Square*>(m_drawables.back().get());

	m_buffers.createVertexBuffers(square->getVertices());
	m_buffers.createElementBuffer(square->getIndices());

	m_texture.createTexture("Images/test.png");

	m_shaders.addShader("Shaders/cube.vert", GL_VERTEX_SHADER);
	m_shaders.addShader("Shaders/cube.frag", GL_FRAGMENT_SHADER);
	m_shaders.compileProgram();
	
	m_camera.setCameraCenter(glm::vec3(0, 0, 0));
	m_camera.setCameraPosition(glm::vec3(0, 0, 1));

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	run();
}

void Game::run()
{
	m_Timer.startTime();
	m_Timer.setTimeStep(60);
	while (m_window.isOpen())
	{
		m_Timer.sleepCycle();
		update(static_cast<float>(m_Timer.getFrameTime()));
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
					glViewport(0, 0, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y));
					m_camera.setOrtho(0, size.x, 0, size.y, .01f, 10000.0f);
				}
			}
		}
	}
	m_eventManager.getKeyboardState();
	m_eventManager.getMouseState();
}

void Game::update(float time)
{
	m_camera.setCameraPosition(glm::vec3(0, 0, 2));
	auto & model = m_drawables.back()->getModel();
	static bool t;
	if (t == 0)
	{
		model = glm::translate(model, glm::vec3(2560 / 2, 1440 / 2, 0));
		model = glm::scale(model, glm::vec3(150, 150, 1));
	}
	t++;
	m_shaders.useProgram();
	m_shaders.glUniformMatrix(m_shaders.getUniformLocation("Model"), GL_FALSE, m_camera.getProj() * m_camera.getView() * model);
	m_shaders.unuseProgram();
}

void Game::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_buffers.bindBuffers();
	m_shaders.useProgram();
	m_texture.bindTexture();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	m_texture.unbindTexture();
	m_shaders.unuseProgram();
	m_buffers.unbindBuffers();
	m_window.display();
}