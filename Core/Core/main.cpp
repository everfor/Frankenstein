#include <iostream>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "display.h"

int main(int argc, char *argv[])
{
	Display window;
	
	while (!window.closed())
	{
		window.update();
	}
	
	return 0;
}