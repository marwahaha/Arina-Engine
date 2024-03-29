#pragma once

#include <SDL2\SDL.h>
#include "Window.h"
#include "Timing.h"
#include "Util.h"
#include "Game.h"

class MainComponent
{
public:
	MainComponent(const int width, const int height, const std::string title);
	~MainComponent();

	void start();
	void stop();

private:
	Window _window;
	Game _game;
	bool isRunning;

	void run();
	void render();
	void cleanUp();
};

