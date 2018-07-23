#include "InputManager.hpp"

lumi::InputManager::InputManager()
{
}

lumi::InputManager::~InputManager()
{
}

bool lumi::InputManager::getEvent()
{
	return static_cast<bool>(SDL_PollEvent(&m_pCurrentEvent));
}

bool lumi::InputManager::isKeyPressed(int key)
{
	if (m_pCurrentEvent.type == SDL_KEYDOWN)
	{
		if (m_pCurrentEvent.key.keysym.sym == key)
		{
			return true;
		}
	}
	return false;
}

bool lumi::InputManager::isMousePressed(int button)
{
	if (m_pCurrentEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (m_pCurrentEvent.button.button == button)
		{
			return true;
		}
	}
	return false;
}