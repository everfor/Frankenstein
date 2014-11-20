#include <iostream>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "core_engine.h"
#include "test_game.h"

// Safeguard for SDL when the Linker System is Console
#undef main

int main(int argc, char *argv[])
{
	CoreEngine core;
	TestGame game(&core);

	core.setGame(&game);
	core.start();

	return 0;
}