#pragma once

#include "object.h"

class RenderingEngine;

class Game
{
	public:
		Game() : root(Object()) {};
		virtual ~Game() {};
		virtual void input(float delta) { getRoot().input(delta); };
		virtual void update(float delta) { getRoot().update(delta); };
		void render(RenderingEngine *engine);
		void addObject(Object *object) { root.addChild(object); };
	private:
		Object& getRoot() { return root; };
		Object root;
};

