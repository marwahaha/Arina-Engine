#include "Window.h"

Window::Window(int width, int height, std::string title) :
	_width(width),
	_height(height),
	_title(title),
	_input(this)
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

	SDL_GL_SetSwapInterval(0);

}

void Window::update()
{
	for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
	{
		_input.setMouseDown(i, false);
		_input.setMouseUp(i, false);
	}

	for (int i = 0; i < Input::NUM_KEYS; i++)
	{
		_input.setKeyDown(i, false);
		_input.setKeyUp(i, false);
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			_isCloseRequested = true;
		}

		if (e.type == SDL_MOUSEMOTION)
		{
			_input.setMouseX(e.motion.x);
			_input.setMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
			int value = e.key.keysym.scancode;

			_input.setKey(value, true);
			_input.setKeyDown(value, true);
		}
		if (e.type == SDL_KEYUP)
		{
			int value = e.key.keysym.scancode;

			_input.setKey(value, false);
			_input.setKeyUp(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			int value = e.button.button;

			_input.setMouse(value, true);
			_input.setMouseDown(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
			int value = e.button.button;

			_input.setMouse(value, false);
			_input.setMouseUp(value, true);
		}
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
