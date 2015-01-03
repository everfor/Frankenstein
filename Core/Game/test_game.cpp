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
#include "movement.h"
#include "rotation.h"
#include "rigid_body.h"
#include "collider.h"
#include "sphere_collider.h"
#include "audio.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

TestGame::TestGame(CoreEngine *core, bool enable_phys) :
		Game(core, enable_phys)
{
	Input::Initialize();

	// Common mesh
	Mesh *planeMesh = new Mesh("./res/models/terrain.obj");
	Mesh *smallPlaneMesh = new Mesh("./res/models/sphere.obj");

	// TEST
	Material *brick = new Material(0.1, 1024, "./res/textures/bricks.jpg", "./res/textures/bricks_normal.jpg", "./res/textures/bricks_disp.png", 0.03f, -0.5f);
	Material *brick2 = new Material(0.1, 2048, "./res/textures/bricks2.jpg", "./res/textures/bricks2_normal.jpg", "./res/textures/bricks2_disp.jpg", 0.03f, -1.0f);
	Material *cave = new Material(0.5, 512, "./res/textures/cave.png");

	// Planes
	Object *bigPlane = new Object();
	bigPlane->addComponent(new MeshRenderer(planeMesh, brick));
	bigPlane->getTransform().moveY(-2);
	// bigPlane->getTransform().rotateX(-90);

	Object *sphere1 = new Object();
	sphere1->addComponent(new MeshRenderer(smallPlaneMesh, brick2));
	RigidBody *rigidBody1 = new RigidBody(glm::vec3(0.2, 0.0, -0.05), glm::vec3(), glm::vec3(), glm::vec3(), 1.0f, 0.9f, 0.2f, 0.2f);
	rigidBody1->setCollider(new SphereCollider(1.0f));
	sphere1->addComponent(rigidBody1);
	sphere1->getTransform().moveX(-3.0);
	sphere1->getTransform().moveY(-0.8);
	//smallPlane->getTransform().rotateX(-90);


	Object *sphere2 = new Object();
	sphere2->addComponent(new MeshRenderer(smallPlaneMesh, cave));
	RigidBody *rigidBody2 = new RigidBody(glm::vec3(-0.4, 0.0, 0.1), glm::vec3(), glm::vec3(0, 0.05, 0), glm::vec3(), 10.0f, 1.0f, 0.2f, 0.2f);
	rigidBody2->setCollider(new SphereCollider(1.0f));
	sphere2->addComponent(rigidBody2);
	sphere2->getTransform().moveZ(0.25);
	sphere2->getTransform().moveX(3.0);
	sphere2->getTransform().moveY(-0.8);

	// Object
	addObject(bigPlane);
	addObject(sphere1);
	addObject(sphere2);

	//Object *pointLight = new Object();
	//pointLight->addComponent(new PointLight(BaseLight(glm::vec3(0, 1, 0), 0.3f), 0, 0, 1));
	//pointLight->getTransform().setTranslation(glm::vec3(1, 0, 1));

	Object *directionalLight = new Object();
	directionalLight->addComponent(new DirectionalLight(BaseLight(glm::vec3(1, 1, 1), 0.7f)));
	directionalLight->getTransform().rotateY(40);
	directionalLight->getTransform().rotateZ(-45);
	directionalLight->getTransform().rotateX(-90);

	Object *spotLight = new Object();
	spotLight->addComponent(new SpotLight(PointLight(BaseLight(glm::vec3(1, 1, 0), 0.7f), 0, 0, 0.3), 70.0f));
	spotLight->getTransform().setTranslation(0, 1.5, 0);
	spotLight->getTransform().rotateX(-90);

	camera = new Object();
	camera->addComponent(new Camera(60.0f, 800.0 / 600.0, 0.1, 10000));
	camera->addComponent(new Movement());
	camera->addComponent(new Rotation());
	camera->getTransform().setTranslation(0, 0, 2);

	//addObject(pointLight);
	addObject(spotLight);
	addObject(directionalLight);
	addObject(camera);

	// Set background music
	engine->getAudioEngine()->setBackgroundAudio(new Audio("./res/audios/interstellar.wav"));

	Material::_load_textures();
	engine->getAudioEngine()->loadResource();
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
		glm::vec2 cursor = Input::GetCurrentCursor();
		std::cout << "x: " << cursor.x << " y: " << cursor.y << std::endl;
	}
}

void TestGame::update(float delta)
{
	Game::update(delta);
}