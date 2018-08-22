#include "Window.hpp"
#include <glad/glad.h>
#include <iostream>

void  APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

lumi::system::Window::Window()
{
	m_shouldClose = true;
	m_fullscreen = false;
}

lumi::system::Window::~Window()
{
	SDL_Quit();
}

bool lumi::system::Window::createWindow(std::string title, int xPos, int yPos, int width, int height, unsigned int flags)
{
	// Set SDL as ready and init SDL
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Init Error", "Could not init SDL2", NULL);
		SDL_Quit();
		return false;
	}

	SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

	// Request an OpenGL 4.5 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	// hardware accel, double buffer, and depth size
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// create the window
	m_pWindow = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, flags);
	if (m_pWindow == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Window Error", "Could not create a window", NULL);
		SDL_Quit();
		return false;
	}
	SDL_MaximizeWindow(m_pWindow);
	// create the openGL context
	m_glContext = SDL_GL_CreateContext(m_pWindow);
	if (m_glContext == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Window Error", "Could not create an openGL context with version 4.5", NULL);
		SDL_Quit();
		return false;
	}

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	GLint glFlags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &glFlags);
	if (glFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		std::cout << "Debug mode enabled" << std::endl;
	}

	m_shouldClose = false; 
	return true;
}

bool lumi::system::Window::isOpen()
{
	return !m_shouldClose;
}

void lumi::system::Window::closeWindow()
{
	m_shouldClose = true;
}

void lumi::system::Window::display()
{
	SDL_GL_SwapWindow(m_pWindow);
}

void lumi::system::Window::toggleFullScreen()
{
	if(!m_fullscreen)
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(m_pWindow, 0);

	m_fullscreen = !m_fullscreen;

}

glm::vec2 lumi::system::Window::getSize()
{
	int width, height;
	SDL_GetWindowSize(m_pWindow, &width, &height);
	return glm::vec2(width, height);
}
