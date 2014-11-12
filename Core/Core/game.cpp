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
#include "spot_light.h"

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
	material.getTexture().setTexture("./res/textures/metal.png");
	material.setSpecularIntensity(0.8);
	material.setSpecularExponent(4);

	// Set lighting
	PhongShader::setAmbientLight(glm::vec3(0.1, 0.1, 0.1));
	// Directional Light
	PhongShader::setDirectionalLight(DirectionalLight(BaseLight(glm::vec3(1, 1, 1), 0.7f), glm::vec3(1, -0.8, -0.3)));
	// Point Light
	PhongShader::addPointLight(PointLight(BaseLight(glm::vec3(1, 0, 0), 0.8f), glm::vec3(-1.5, 0, 1), 0, 0, 1, 10));
	PhongShader::addPointLight(PointLight(BaseLight(glm::vec3(0, 0, 1), 0.8f), glm::vec3(1.5, 0, 1), 0, 0, 1, 10));
	// Spot Light
	PhongShader::addSpotLight(SpotLight(PointLight(BaseLight(glm::vec3(1, 1, 0), 0.8f), glm::vec3(0, 3, 0), 0, 0, 0.5, 10), glm::vec3(0, -1, 0), 0.8));
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
	cos_var = cosf(temp);

	// TEST TRANSFORMATION
	// transform.setTranslation(sin_var, 0, 0);
	transform.setRotation(0, sin_var * 180, 0);
	// transform.setScale(0.5, 0.5, 0.5);

	PhongShader::getPointLights()[0].setPos(glm::vec3(-1.5, 3 * sin_var, 1));
	PhongShader::getPointLights()[1].setPos(glm::vec3(1.5, 3 * cos_var, 1));
}

void Game::render()
{
	shader->bind();
	shader->updateUniforms(transform, camera, material);
	// material.getTexture().bind();
	mesh.draw();
}