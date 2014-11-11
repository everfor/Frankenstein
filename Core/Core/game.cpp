#include "game.h"
#include "input.h"
#include "vertex.h"
#include "resource_manager.h"
#include "timer.h"
#include "basic_shader.h"
#include "phong_shader.h"
#include "directional_light.h"
#include "base_light.h"
#include "point_light.h"

#include <iostream>

Game::Game() :
		mesh(Mesh()), shader(PhongShader::GetShader()), transform(Transform()), camera(Camera(80.0f, 800.0f / 600.0f, 0.1f, 1000)), material(Material(Texture(), glm::vec3(1, 1, 1)))
{
	Input::Initialize();

	// TEST MESH
	ResourceManager::LoadMesh(std::string("./res/models/monkey.obj"), mesh);

	// TEST TEXTURE
	// Somehow opengl refuses to render texture if I dont get a reference for the texture object
	texture = material.getTexture();
	material.getTexture().setTexture("./res/textures/shaft.jpg");
	material.setSpecularIntensity(3);
	material.setSpecularExponent(64);

	// Set lighting
	PhongShader::setAmbientLight(glm::vec3(0.1, 0.1, 0.1));
	// Directional Light
	PhongShader::setDirectionalLight(DirectionalLight(BaseLight(glm::vec3(1, 1, 1), 0.9f), glm::vec3(1, -0.5, 0.3)));
	// Point Light
	PhongShader::addPointLight(PointLight(BaseLight(glm::vec3(1, 0, 0), 0.8f), glm::vec3(-2, 0, 1), 0, 0, 1));
	PhongShader::addPointLight(PointLight(BaseLight(glm::vec3(0, 0, 1), 0.8f), glm::vec3(2, 0, 1), 0, 0, 1));
}

Game::~Game()
{
	BasicShader::DestroyShader();
}

static float move_amt = 0.05;
void Game::input()
{
	if (Input::GetKeyDown(MOUSE_LEFT))
	{
		std::cout << "Left mouse down!" << std::endl;
	}
	if (Input::GetKeyUp(MOUSE_LEFT))
	{
		std::cout << "Left mouse up!" << std::endl;
		glm::vec2 cursor = Input::GetCursorPosition();
		std::cout << "x: " << cursor.x << " y: " << cursor.y << std::endl;
	}
	if (Input::GetKeyDown(KEY_UP))
	{
		camera.moveY(move_amt);
	}
	if (Input::GetKeyDown(KEY_DOWN))
	{
		camera.moveY(0 - move_amt);
	}
}

static float sin_var = 0.0f;
static float cos_var = 0.0f;

void Game::update()
{
	Input::Update();

	// TEST uniform
	static float temp = 0.0f;
	temp += Timer::getDelta() / 1000.0;
	sin_var = sinf(temp);

	// TEST TRANSFORMATION
	// transform.setTranslation(sin_var, 0, 0);
	transform.setRotation(0, sin_var * 180, 0);
	// transform.setScale(0.5, 0.5, 0.5);
}

void Game::render()
{
	shader->bind();
	shader->updateUniforms(transform, camera, material);
	// material.getTexture().bind();
	mesh.draw();
}