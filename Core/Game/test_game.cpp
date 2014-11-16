#include "test_game.h"
#include "input.h"
#include "vertex.h"
#include "resource_manager.h"
#include "timer.h"
#include "directional_light.h"
#include "base_light.h"
#include "point_light.h"
#include "spot_light.h"
#include "mesh_renderer.h"
#include "camera.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

TestGame::TestGame() :
		Game()
{
	Input::Initialize();

	// TEST
	Material *material = new Material();
	Mesh *mesh = new Mesh();

	ResourceManager::LoadMesh(std::string("./res/models/monkey.obj"), *mesh);
	
	texture = new Texture();
	texture->setTexture("./res/textures/metal.png");

	material->addTexture(MATERIAL_DIFFUSE_TEXTURE, *texture);
	material->addFloat(MATERIAL_SPECULAR_INTENSITY, 0.8);
	material->addFloat(MATERIAL_SPECULAR_EXPONENT, 4);

	// Monkeys
	Object *monkey1 = new Object();
	Object *monkey2 = new Object();
	monkey2->addComponent(new MeshRenderer(mesh, material));
	monkey2->getTransform().setTranslation(2.8, 0, 0);
	monkey1->addComponent(new MeshRenderer(mesh, material));
	monkey1->getTransform().setTranslation(0, 1.5, 1.5);
	monkey1->addChild(monkey2);

	monkey = new Object();
	monkey->addComponent(new MeshRenderer(mesh, material));
	monkey->addChild(monkey1);
	monkey->getTransform().setScale(0.3, 0.3, 0.3);

	// Object
	addObject(monkey);

	Object *pointLight = new Object();
	pointLight->addComponent(new PointLight(BaseLight(glm::vec3(0, 1, 0), 0.3f), 0, 0, 1));
	pointLight->getTransform().setTranslation(glm::vec3(1, 0, 1));

	Object *directionalLight = new Object();
	directionalLight->addComponent(new DirectionalLight(BaseLight(glm::vec3(1, 0, 0), 0.4f)));
	directionalLight->getTransform().rotateY(-90);
	directionalLight->getTransform().rotateZ(-45);

	Object *spotLight = new Object();
	spotLight->addComponent(new SpotLight(PointLight(BaseLight(glm::vec3(0, 0, 1), 0.3f), 0, 0, 1), 0.5f));
	spotLight->getTransform().setTranslation(0, -1, 0);
	spotLight->getTransform().setRotation(glm::rotate(glm::quat(1, 0, 0, 0), 90.0f, glm::vec3(1, 0, 0)));

	camera = new Object();
	camera->addComponent(new Camera(80.0f, 800.0 / 600.0, 0.1, 10000));
	camera->getTransform().setTranslation(0, 0, 2);

	addObject(pointLight);
	addObject(directionalLight);
	addObject(spotLight);
	addObject(camera);
}

TestGame::~TestGame()
{
}

void TestGame::input(float delta)
{
	Game::input(delta);

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
	Game::update(delta);

	// TEST uniform
	static float temp = 0.0f;
	temp += delta;
	sin_var = sinf(temp);
	cos_var = cosf(temp);

	// TEST TRANSFORMATION
	// transform.setTranslation(sin_var, 0, 0);
	monkey->getTransform().setRotation(glm::rotate(glm::quat(1, 0, 0, 0), sin_var * 180, glm::vec3(0, 1, 0)));
	camera->getTransform().setTranslation(sin_var, 0, 2 + sin_var);
	// transform.setScale(0.5, 0.5, 0.5);
}