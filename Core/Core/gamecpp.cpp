#include "game.h"
#include "rendering_engine.h"

void Game::render(RenderingEngine *engine)
{
	engine->render(root);
}