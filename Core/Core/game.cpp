#include "game.h"
#include "input.h"
#include "vertex.h"
#include "resource_manager.h"
#include "timer.h"

#include <iostream>

Game::Game() :
		mesh(Mesh()), shader(Shader()), transform(Transform()), camera(Camera(80.0f, 800.0f / 600.0f, 0.1f, 1000)), texture(Texture())
{
	Input::Initialize();

	// TEST MESH
	//Vertex vertices[] = { Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)), Vertex(glm::vec3(0.0f, 1.0f, 0.0f)), Vertex(glm::vec3(1.0f, -1.0f, 0)), Vertex(glm::vec3(0.0f, -1.0f, 1.0f)) };
	//unsigned short indices[] = { 0, 1, 3, 3, 1, 2, 3, 2, 1, 0, 2, 3 };
	//mesh.addVertices(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	ResourceManager::LoadMesh(std::string("./res/models/monkey.obj"), mesh);

	// TEST SHADER
	std::string vertex_shader_str, fragment_shader_str;
	ResourceManager::LoadShader("./res/shaders/basicShader.vs", vertex_shader_str);
	ResourceManager::LoadShader("./res/shaders/basicShader.fs", fragment_shader_str);
	shader.addVertexShader(vertex_shader_str);
	shader.addFragmentShader(fragment_shader_str);
	shader.compileAllShaders();

	// TEST UNIFORM
	shader.addUniform("transform");

	// Set transform
	// Transform::setProjection(100.0f, 800.0f, 600.0f, 0.1f, 1000);

	// TEST TEXTURE
	texture.setTexture("./res/textures/test.png");
}

Game::~Game()
{
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
	shader.bind();
	shader.setUniform("transform", camera.getCameraProjection() * transform.getTransformation());
	texture.bind();
	mesh.draw();
}