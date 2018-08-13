#include "EventManager.hpp"

lumi::system::EventManager::EventManager()
{
}

lumi::system::EventManager::~EventManager()
{
}

bool lumi::system::EventManager::getEvent()
{
	return static_cast<bool>(SDL_PollEvent(&m_pCurrentEvent));
}

void lumi::system::EventManager::getKeyboardState()
{
	m_keyboardState = const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
}

void lumi::system::EventManager::getMouseState()
{
	m_mouseState = SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);
}

bool lumi::system::EventManager::eventTriggered(unsigned int type)
{
	if (m_pCurrentEvent.type == type)
		return true;
	return false;
}

bool lumi::system::EventManager::isWindowEvent(unsigned int type)
{
	if (m_pCurrentEvent.window.event == type)
		return true;
	return false;
}

glm::vec2 lumi::system::EventManager::getWindowSize()
{
	return glm::vec2(m_pCurrentEvent.window.data1, m_pCurrentEvent.window.data2);
}

bool lumi::system::EventManager::isKeyPressed(int key, bool useEvents)
{
	if (useEvents)
	{
		if (eventTriggered(SDL_KEYDOWN))
		{
			if (m_pCurrentEvent.key.keysym.sym == key)
			{
				return true;
			}
		}
	}
	else
	{
		if (m_keyboardState[key])
			return true;
	}
	return false;
}

bool lumi::system::EventManager::isMousePressed(int button, bool useEvents)
{
	if (useEvents)
	{
		if (eventTriggered(SDL_MOUSEBUTTONDOWN))
		{
			if (m_pCurrentEvent.button.button == button)
			{
				return true;
			}
		}
	}
	else
	{
		if (m_mouseState & SDL_BUTTON(button))
			return true;
	}
	return false;
}