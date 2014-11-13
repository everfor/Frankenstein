#include "test_game.h"
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
#include "mesh_renderer.h"

#include <iostream>
#include <glm\glm.hpp>

TestGame::TestGame() :
		Game()
{
	Input::Initialize();

	// TEST
	Material *material = new Material(Texture(), glm::vec3(1, 1, 1));
	Mesh *mesh = new Mesh();

	ResourceManager::LoadMesh(std::string("./res/models/monkey.obj"), *mesh);
	material->getTexture().setTexture("./res/textures/metal.png");
	material->setSpecularIntensity(0.8);
	material->setSpecularExponent(4);

	// Object
	//Object *monkey = new Object();
	//monkey->addComponent(new MeshRenderer(mesh, material));
	//getRoot().addChild(monkey);
	getRoot().addComponent(new MeshRenderer(mesh, material));

	// Lighting will be massively refactored
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

TestGame::~TestGame()
{
	BasicShader::DestroyShader();
}

void TestGame::input(float delta)
{
	getRoot().input(delta);
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
}

static float sin_var = 0.0f;
static float cos_var = 0.0f;

void TestGame::update(float delta)
{
	getRoot().update(delta);
	// TEST uniform
	static float temp = 0.0f;
	temp += delta;
	sin_var = sinf(temp);
	cos_var = cosf(temp);

	// TEST TRANSFORMATION
	// transform.setTranslation(sin_var, 0, 0);
	getRoot().getTransform().setRotation(0, sin_var * 180, 0);
	// transform.setScale(0.5, 0.5, 0.5);

	PhongShader::getPointLights()[0].setPos(glm::vec3(-1.5, 3 * sin_var, 1));
	PhongShader::getPointLights()[1].setPos(glm::vec3(1.5, 3 * cos_var, 1));
}