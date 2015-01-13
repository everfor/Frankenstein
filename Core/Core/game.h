#pragma once

#include "object.h"

class CoreEngine;

class Game
{
	public:
		Game(CoreEngine* core, bool if_enable_phys = true, bool if_enable_audio = true) : engine(core), root(Object()), enablePhysicsEngine(if_enable_phys), enableAudioEngine(if_enable_audio) { root.setEngine(engine); };
		virtual ~Game() {};
		virtual void input(float delta) { getRoot().input(delta); };
		virtual void update(float delta);
		void render();
		void addObject(Object *object) { root.addChild(object); };
		void setBackgroundMusic(const std::string& file_name);
		void setEngine(CoreEngine *new_engine);
		bool physicsEngineEnabled() { return enablePhysicsEngine; };
		bool audioEngineEnabled() { return enableAudioEngine; };
	protected:
		CoreEngine *engine;
	private:
		Object& getRoot() { return root; };
		Object root;
		// Whether or not to enable default physics engine
		bool enablePhysicsEngine;
		// Whether or not to enable default audio engine
		bool enableAudioEngine;
};

