#pragma once

#include "object.h"

class Game
{
	public:
		Game() : root(Object()) {};
		virtual ~Game() {};
		virtual void input(float delta) { getRoot().input(delta); };
		virtual void update(float delta) { getRoot().update(delta); };
		Object& getRoot() { return root; };
	private:
		Object root;
};

