#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <memory>
#include <glm/vec2.hpp>

namespace lumi
{
	namespace system
	{
		class EventManager
		{
		public:
			EventManager();
			~EventManager();

			// Gets the next event in the event queue, if there are no more events then this returns false
			bool getEvent();
			void getKeyboardState();
			void getMouseState();
			bool eventTriggered(unsigned int type);
			bool isWindowEvent(unsigned int type);
			glm::vec2 getWindowSize();
			bool isKeyPressed(int key, bool useEvents = true);
			bool isMousePressed(int button, bool useEvents = true);
		private:
			SDL_Event m_pCurrentEvent;
			Uint8 * m_keyboardState;
			Uint32 m_mouseState;
			glm::ivec2 m_mousePos;
		};
	};
}