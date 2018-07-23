#pragma once
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
namespace lumi
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		// Gets the next event in the event queue, if there are no more events then this returns false
		bool getEvent();
		bool isKeyPressed(int key);
		bool isMousePressed(int button);
	private:
		SDL_Event m_pCurrentEvent;
	};
}