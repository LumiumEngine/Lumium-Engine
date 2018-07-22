#include "InputManager.hpp"

lumi::InputManager::InputManager()
{
	m_pCurrentEvent = nullptr;
}

lumi::InputManager::~InputManager()
{
	m_pCurrentEvent = nullptr;
}

void lumi::InputManager::setEvent(SDL_Event * event)
{
	m_pCurrentEvent = event;
}

bool lumi::InputManager::isKeyPressed(int key)
{
	if (m_pCurrentEvent->type == SDL_KEYDOWN)
	{
		if (m_pCurrentEvent->key.keysym.sym == key)
		{
			return true;
		}
	}
	return false;
}

bool lumi::InputManager::isMousePressed(int button)
{
	if (m_pCurrentEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (m_pCurrentEvent->button.button == button)
		{
			return true;
		}
	}
	return false;
}