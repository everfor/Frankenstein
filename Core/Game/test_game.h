#pragma once

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "texture.h"
#include "material.h"
#include "game.h"
#include "object.h"

class TestGame : public Game
{
	public:
		TestGame();
		virtual ~TestGame();
		void input(float delta) override;
		void update(float delta) override;
	private:
		Object *monkey;
		Object *camera;
		Texture *texture;
};

