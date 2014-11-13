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
		void input() override;
		void update() override;
};

