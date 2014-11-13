#pragma once

#include "object.h"

class Game
{
	public:
		Game() : root(Object()) {};
		virtual ~Game() {};
		virtual void input() { getRoot().input(); };
		virtual void update() { getRoot().update(); };
		Object& getRoot() { return root; };
	private:
		Object root;
};

