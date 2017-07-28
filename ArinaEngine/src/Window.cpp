#include "Window.h"

Window::Window(int width, int height, std::string title) :
	_width(width),
	_height(height),
	_title(title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization error : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (_window == 0)
	{
		std::cout << "Window creation failed : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return;
	}

	_glContext = SDL_GL_CreateContext(_window);
	if (_glContext == 0)
	{
		std::cout << "OpenGL context creation failed : " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_window);
		SDL_Quit();
		return;
	}

#ifdef _WIN32

	GLenum glewInit(glewInit());
	if (glewInit != GLEW_OK)
	{
		std::cout << "GLEW initialization failed : " << glewGetErrorString(glewInit);
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_window);
		SDL_Quit();
		return;
	}
#endif
}

void Window::update()
{
	while (!_isCloseRequested)
	{
		SDL_WaitEvent(&_events);
		if (_events.window.event == SDL_WINDOWEVENT_CLOSE)
			_isCloseRequested = true;

		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(_window);
	}
}

void Window::swapBuffer()
{
	SDL_GL_SwapWindow(_window);
}

Window::~Window()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
