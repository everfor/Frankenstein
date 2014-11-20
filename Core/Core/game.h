#pragma once

#include "object.h"

class RenderingEngine;
class CoreEngine;

class Game
{
	public:
		Game(CoreEngine* core) : engine(core), root(Object()) { root.setEngine(engine); };
		virtual ~Game() {};
		virtual void input(float delta) { getRoot().input(delta); };
		virtual void update(float delta) { getRoot().update(delta); };
		void render();
		void addObject(Object *object) { root.addChild(object); };
		void setEngine(CoreEngine *new_engine);
	protected:
		CoreEngine *engine;
	private:
		Object& getRoot() { return root; };
		Object root;
};

