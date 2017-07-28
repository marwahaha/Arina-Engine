#include "Window.h"
#include "MainComponent.h"

static const int WIDTH = 800;
static const int HEIGHT = 600;
static const std::string TITLE = "Arina Engine";

int main(int argc, char **argv)
{
	MainComponent game(WIDTH, HEIGHT, TITLE);
	game.start();
	return 0;
}
