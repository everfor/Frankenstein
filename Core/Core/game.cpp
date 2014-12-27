#include "game.h"
#include "core_engine.h"
#include "rendering_engine.h"

void Game::render()
{
	engine->getRenderingEngine()->render(root);
}

void Game::setEngine(CoreEngine *new_engine)
{
	engine = new_engine;
	getRoot().setEngine(engine);
}

void Game::update(float delta)
{
	engine->getPhysicsEngine()->update(delta);
	getRoot().update(delta);
}