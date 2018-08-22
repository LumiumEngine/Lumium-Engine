#pragma once
#include <LumiumEngine/Graphics/Buffers.hpp>
#include <LumiumEngine/Graphics/Drawable.hpp>
#include <LumiumEngine/Graphics/Font.hpp>
#include <LumiumEngine/Graphics/Text.hpp>
#include <LumiumEngine/Graphics/Texture.hpp>

#include <LumiumEngine/System/Camera.hpp>
#include <LumiumEngine/System/EventManager.hpp>
#include <LumiumEngine/System/Shaders.hpp>
#include <LumiumEngine/System/Timer.hpp>
#include <LumiumEngine/System/Window.hpp>

#include <vector>
#include <memory>

class Game
{
public:
	Game();
	~Game();

	void start();
private:
	void setup();
	void run();
	void processInput();
	void update(float time);
	void display();
private:
	lumi::system::Window m_window;;
	lumi::system::EventManager m_eventManager;
	lumi::system::Timer m_Timer;
	std::vector<std::unique_ptr<lumi::graphics::Drawable>> m_drawables;
	lumi::graphics::Buffers m_buffers;
	lumi::graphics::Texture m_texture;
	lumi::system::Shaders m_shaders;
	lumi::system::Camera m_camera;
	std::shared_ptr<lumi::graphics::Font> m_font;
	lumi::graphics::Text m_text;
};