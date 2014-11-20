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
#include "core_engine.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

TestGame::TestGame(CoreEngine *core) :
		Game(core)
{
	Input::Initialize();

	// Common mesh
	Mesh *mesh = new Mesh("./res/models/monkey.obj");
	Mesh *mesh2 = new Mesh("./res/models/plane.obj");

	// TEST
	Material *metal = new Material();
	Material *wood = new Material();
	Material *cave = new Material();
	
	Texture *metalTex = new Texture("./res/textures/metal.png");
	Texture *woodTex = new Texture("./res/textures/wood.png");
	Texture *caveTex = new Texture("./res/textures/cave.png");
	TextureResource::_load_all();

	metal->addTexture(MATERIAL_DIFFUSE_TEXTURE, *metalTex);
	metal->addFloat(MATERIAL_SPECULAR_INTENSITY, 0.8);
	metal->addFloat(MATERIAL_SPECULAR_EXPONENT, 4);

	wood->addTexture(MATERIAL_DIFFUSE_TEXTURE, *woodTex);
	wood->addFloat(MATERIAL_SPECULAR_INTENSITY, 0.1);
	wood->addFloat(MATERIAL_SPECULAR_EXPONENT, 1024);

	cave->addTexture(MATERIAL_DIFFUSE_TEXTURE, *caveTex);
	cave->addFloat(MATERIAL_SPECULAR_INTENSITY, 0.2);
	cave->addFloat(MATERIAL_SPECULAR_EXPONENT, 128);

	// Monkeys
	monkey1 = new Object();
	monkey2 = new Object();
	monkey2->addComponent(new MeshRenderer(mesh, metal));
	monkey2->getTransform().setTranslation(2, 0, 0);
	monkey2->getTransform().setScale(0.6, 0.6, 0.6);
	monkey1->addComponent(new MeshRenderer(mesh, wood));
	monkey1->getTransform().setTranslation(3, 0, 0);
	monkey1->getTransform().setScale(0.7, 0.7, 0.7);
	monkey1->addChild(monkey2);

	monkey = new Object();
	monkey->addComponent(new MeshRenderer(mesh, cave));
	monkey->addChild(monkey1);
	monkey->getTransform().setScale(0.5, 0.5, 0.5);

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
	TextureResource::_clear();
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
static float last_sin = 0.0f;

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
	// monkey->getTransform().setRotation(glm::rotate(glm::quat(1, 0, 0, 0), sin_var * 180, glm::vec3(0, 1, 0)));
	monkey->getTransform().rotateY((sin_var - last_sin) * 180);
	monkey1->getTransform().rotateY((sin_var - last_sin) * 180);
	monkey2->getTransform().rotateY((sin_var - last_sin) * 180);
	// camera->getTransform().setTranslation(sin_var, 0, 2 + sin_var);
	last_sin = sin_var;
	// camera->getTransform().rotateY(sin_var);
	// transform.setScale(0.5, 0.5, 0.5);
}