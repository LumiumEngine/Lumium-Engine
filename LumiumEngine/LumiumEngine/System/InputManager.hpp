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

		void setEvent(SDL_Event * event);
		bool isKeyPressed(int key);
		bool isMousePressed(int button);
	private:
		SDL_Event * m_pCurrentEvent;
	};
}