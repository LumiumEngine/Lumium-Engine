#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>
#include <glm/vec2.hpp>

namespace lumi
{
	namespace system 
	{
		class Window
		{
		public:
			Window();
			~Window();

			bool createWindow(std::string title, int xPos, int yPos, int width, int height, unsigned int flags);
			bool isOpen();
			void closeWindow();
			void display();
			void toggleFullScreen();
			glm::vec2 getSize();
		private:
			SDL_Window * m_pWindow;
			SDL_GLContext m_glContext;

			bool m_fullscreen;
			bool m_shouldClose;
		};
	};
}