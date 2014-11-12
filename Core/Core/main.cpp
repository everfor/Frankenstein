#include <iostream>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "core.h"

// Safeguard for SDL when the Linker System is Console
#undef main

int main(int argc, char *argv[])
{
	Core core;
	Game game;

	core.setGame(&game);
	core.start();
	
	return 0;
}