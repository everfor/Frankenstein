#pragma once

#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "texture.h"
#include "material.h"
#include "game.h"

class TestGame : public Game
{
public:
	TestGame();
	virtual ~TestGame();
	void input() override;
	void update() override;
	void render() override;
private:
	Mesh mesh;
	Shader* shader;
	Transform transform;
	Camera camera;
	Material material;
	Texture texture;
};

