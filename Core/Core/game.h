#pragma once

#include "mesh.h"
#include "shader.h"
#include "transform.h"

class Game
{
	public:
		Game();
		virtual ~Game();
		void input();
		void update();
		void render();
	private:
		Mesh mesh;
		Shader shader;
		Transform transform;
};

