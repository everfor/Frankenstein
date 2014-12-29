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

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

TestGame::TestGame(CoreEngine *core, bool enable_phys) :
		Game(core, enable_phys)
{
	Input::Initialize();

	// Common mesh
	// Mesh *mesh = new Mesh("./res/models/monkey.obj");
	Mesh *planeMesh = new Mesh("./res/models/terrain.obj");
	Mesh *smallPlaneMesh = new Mesh("./res/models/sphere.obj");

	// TEST
	Material *brick = new Material(0.1, 1024, "./res/textures/bricks.jpg", "./res/textures/bricks_normal.jpg", "./res/textures/bricks_disp.png", 0.03f, -0.5f);
	Material *brick2 = new Material(0.1, 2048, "./res/textures/bricks2.jpg", "./res/textures/bricks2_normal.jpg", "./res/textures/bricks2_disp.jpg", 0.03f, -1.0f);
	Material *cave = new Material(0.5, 512, "./res/textures/cave.png");

	//cave->addTexture(MATERIAL_DIFFUSE_TEXTURE, *caveTex);
	//cave->addFloat(MATERIAL_SPECULAR_INTENSITY, 0.2);
	//cave->addFloat(MATERIAL_SPECULAR_EXPONENT, 128);

	// Monkeys
	// monkey1 = new Object();
	// monkey2 = new Object();
	// monkey2->addComponent(new MeshRenderer(mesh, metal));
	// monkey2->getTransform().setTranslation(2, 0, 0);
	// monkey2->getTransform().setScale(0.6, 0.6, 0.6);
	// monkey1->addComponent(new MeshRenderer(mesh, wood));
	// monkey1->getTransform().setTranslation(1, 0, 0);
	// monkey1->getTransform().setScale(0.5, 0.5, 0.5);
	//monkey1->addChild(monkey2);

	// Planes
	Object *bigPlane = new Object();
	bigPlane->addComponent(new MeshRenderer(planeMesh, brick));
	bigPlane->getTransform().moveY(-2);
	// bigPlane->getTransform().rotateX(-90);

	Object *sphere1 = new Object();
	sphere1->addComponent(new MeshRenderer(smallPlaneMesh, brick2));
	RigidBody *rigidBody1 = new RigidBody(glm::vec3(0.2, 0.0, -0.1), glm::vec3(), glm::vec3(), glm::vec3(), 1.0f, 0.9f, 0.1f, 0.1f);
	rigidBody1->setCollider(new SphereCollider(1.0f));
	sphere1->addComponent(rigidBody1);
	sphere1->getTransform().moveX(-2.0);
	sphere1->getTransform().moveY(-0.8);
	//smallPlane->getTransform().rotateX(-90);


	Object *sphere2 = new Object();
	sphere2->addComponent(new MeshRenderer(smallPlaneMesh, cave));
	RigidBody *rigidBody2 = new RigidBody(glm::vec3(-0.4, 0.0, 0.2), glm::vec3(), glm::vec3(0, 0.02, 0), glm::vec3(), 10.0f, 1.0f, 0.15f, 0.15f);
	rigidBody2->setCollider(new SphereCollider(1.0f));
	sphere2->addComponent(rigidBody2);
	sphere2->getTransform().moveZ(0.5);
	sphere2->getTransform().moveX(2.0);
	sphere2->getTransform().moveY(-0.8);

	// monkey = new Object();
	// monkey->addComponent(new MeshRenderer(mesh, metal));
	// monkey->addChild(monkey1);
	// monkey->getTransform().setScale(0.5, 0.5, 0.5);
	// monkey->getTransform().setTranslation(-1, 0, 0);

	// Object
	// addObject(monkey);
	// addObject(monkey1);
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

	Material::_load_textures();
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
	// monkey->getTransform().rotateY((sin_var - last_sin) * 180);
	// monkey1->getTransform().rotateY((sin_var - last_sin) * 180);
	// monkey1->getTransform().rotateY((sin_var - last_sin) * 180);
	//monkey2->getTransform().rotateY((sin_var - last_sin) * 180);
	// camera->getTransform().setTranslation(sin_var, 0, 2 + sin_var);
	last_sin = sin_var;
	// camera->getTransform().rotateY(sin_var);
	// transform.setScale(0.5, 0.5, 0.5);
}