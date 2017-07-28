#include "MainComponent.h"



MainComponent::MainComponent(const int width, const int height, const std::string title) :
	_window(width, height, title)
{

}


MainComponent::~MainComponent()
{
}

void MainComponent::start()
{
	run();
}

void MainComponent::stop()
{
}

void MainComponent::run()
{
	//render window
	_window.update();
}

void MainComponent::cleanUp()
{
}
