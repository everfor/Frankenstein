#include "game.h"
#include "core_engine.h"
#include "rendering_engine.h"
#include "audio_engine.h"

void Game::setBackgroundMusic(const std::string& file_name)
{
	engine->getAudioEngine()->setBackgroundAudio(file_name);
}

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
	if (physicsEngineEnabled())
	{
		engine->getPhysicsEngine()->update(delta);
	}

	if (audioEngineEnabled())
	{
		engine->getAudioEngine()->play(delta);
	}
	
	getRoot().update(delta);
}