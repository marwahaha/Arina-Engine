#pragma once

#define GLEW_STATIC

#ifdef _WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL/GL.h>
#endif // _WIN32

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2\SDL.h>
#include <iostream>
#include <string>

class Window
{
public:
	Window(int width, int height, std::string title);
	~Window();
	void update();
	void swapBuffer();
	inline bool isCloseRequested() { return _isCloseRequested; }
	inline int GetWidth()                   const { return _width; }
	inline int GetHeight()                  const { return _height; }
	inline float GetAspect()                const { return (float)_width / (float)_height; }
	inline const std::string& GetTitle()    const { return _title; }
	inline SDL_Window* GetSDLWindow() { return _window; }


private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
	SDL_Event _events;
	bool _isCloseRequested;
	int _width;
	int _height;
	std::string _title;
};

