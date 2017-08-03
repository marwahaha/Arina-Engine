#include "MainComponent.h"
#include "Timing.h"
#include "Util.h"
#include "Game.h"

static const double FRAME_CAP = 5000.0;

MainComponent::MainComponent(const int width, const int height, const std::string title) :
	_window(width, height, title),
	isRunning(false)
{
	Input definiedInput = _window._input;
	_game(definiedInput);
}


MainComponent::~MainComponent()
{
}

void MainComponent::start()
{
	if(!isRunning)
		run();
}

void MainComponent::stop()
{
	if (isRunning)
		isRunning = false;
}

void MainComponent::run()
{
	isRunning = true;

	const double frameTime = 1.0 / FRAME_CAP;

	int frames = 0;
	double frameCounter = 0;

	double lastTime = Time::getTime();
	double unprocessedTime = 0;

	while (isRunning)
	{
		bool render = false;
		double startTime = Time::getTime();
		double passedTime = startTime - lastTime;
		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		while (unprocessedTime > frameTime)
		{
			unprocessedTime -= frameTime;
			render = true;

			_window.update();

			if (_window.isCloseRequested())
				stop();

			Time::deltaTime = frameTime;
			
			_game.input();
			_game.update();

			if (frameCounter >= 1.0)
			{
				std::cout << frames << std::endl;
				frames = 0;
				frameCounter = 0;
			}

		}

		if (render)
		{
			_game.render();
			_window.swapBuffer();
			frames++;
		}
		else
		{
			Util::Sleep(1);
		}

		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(_window._window);
	}
	cleanUp();
}

void MainComponent::cleanUp()
{
	_window.~Window();
}
