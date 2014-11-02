#pragma once

#include "mesh.h"

class Game
{
	public:
		Game();
		virtual ~Game();
		void input();
		void update();
		void render();
	private:
		Mesh mesh;
};

