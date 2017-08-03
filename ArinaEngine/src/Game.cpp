#include "Game.h"
#include <iostream>

Game::Game(Input& input) :
	_input(input)
{
}


Game::~Game()
{
}

void Game::render()
{
}

void Game::input()
{

	if (_input.getKeyDown(Input::KEY_A))
	{
		std::cout << "Key A is now Down" << std::endl;
	}

}

void Game::update()
{
}

