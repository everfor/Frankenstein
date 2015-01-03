#pragma once

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>
#include <memory>

#include "display.h"
#include "game.h"
#include "camera.h"
#include "rendering_engine.h"
#include "physics_engine.h"
#include "audio_engine.h"

#define FRAME_CAP			1000
#define MIN_SLEEP_TIME		1

class CoreEngine
{
	public:
		CoreEngine(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, std::string& title = std::string(DEFAULT_TITLE), int frame_rate = FRAME_CAP,
					float camera_fov = 80.0f, float camera_z_near = 0.1f, float camera_z_far = 1000.0f, glm::vec3& camera_pos = glm::vec3(0, 0, 2));
		virtual ~CoreEngine();
		void setGame(Game *new_game);
		void start();
		void stop();
		RenderingEngine* getRenderingEngine() { return &renderingEngine; };
		PhysicsEngine* getPhysicsEngine() { return &physicsEngine; };
		AudioEngine* getAudioEngine() { return &audioEngine; };
	private:
		void run();
		void render();
		Display *window;
		bool is_running;
		unsigned int frame_rate;
		RenderingEngine renderingEngine;
		PhysicsEngine physicsEngine;
		AudioEngine audioEngine;
		Game *game;
};

