#include "InputManager.hpp"

lumi::system::InputManager::InputManager()
{
}

lumi::system::InputManager::~InputManager()
{
}

bool lumi::system::InputManager::getEvent()
{
	return static_cast<bool>(SDL_PollEvent(&m_pCurrentEvent));
}

bool lumi::system::InputManager::eventTriggered(unsigned int type)
{
	if (m_pCurrentEvent.type == type)
		return true;
	return false;
}

bool lumi::system::InputManager::isKeyPressed(int key)
{
	if (eventTriggered(SDL_KEYDOWN))
	{
		if (m_pCurrentEvent.key.keysym.sym == key)
		{
			return true;
		}
	}
	return false;
}

bool lumi::system::InputManager::isMousePressed(int button)
{
	if (eventTriggered(SDL_MOUSEBUTTONDOWN))
	{
		if (m_pCurrentEvent.button.button == button)
		{
			return true;
		}
	}
	return false;
}