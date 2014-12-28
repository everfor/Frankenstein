#pragma once

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "texture.h"
#include "material.h"
#include "game.h"
#include "object.h"

class CoreEngine;

class TestGame : public Game
{
	public:
		TestGame(CoreEngine *core, bool enable_phys = true);
		virtual ~TestGame();
		void input(float delta) override;
		void update(float delta) override;
	private:
		Object *monkey;
		Object *monkey1;
		Object *monkey2;
		Object *camera;
};

