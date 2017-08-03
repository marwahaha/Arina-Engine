#pragma once

#include "Input.h"

class Game
{
public:
	Game(Input& input);
	~Game();

	void render();
	void input();
	void update();

private:
	Input& _input;

};

