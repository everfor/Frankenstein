#include "game.h"
#include "input.h"
#include "vertex.h"
#include "resource_manager.h"
#include "timer.h"

#include <iostream>

Game::Game() :
		mesh(Mesh()), shader(Shader()), transform(Transform())
{
	Input::Initialize();

	// TEST MESH
	//Vertex vertices[] = { Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)), Vertex(glm::vec3(0.0f, 1.0f, 0.0f)), Vertex(glm::vec3(1.0f, -1.0f, 0)), Vertex(glm::vec3(0.0f, -1.0f, 1.0f)) };
	//unsigned short indices[] = { 0, 1, 3, 3, 1, 2, 3, 2, 1, 0, 2, 3 };
	//mesh.addVertices(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	ResourceManager::loadMesh(std::string("./res/models/monkey.obj"), mesh);

	// TEST SHADER
	shader.addVertexShader(ResourceManager::LoadShader("./res/shaders/basicShader.vs"));
	shader.addFragmentShader(ResourceManager::LoadShader("./res/shaders/basicShader.fs"));
	shader.compileAllShaders();

	// TEST UNIFORM
	shader.addUniform("transform");
}

Game::~Game()
{
}

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
		std::cout << "Up arrow down!" << std::endl;
	}
	if (Input::GetKeyUp(KEY_UP))
	{
		std::cout << "Up arrow up!" << std::endl;
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
	cos_var = abs(cosf(temp));

	// TEST TRANSFORMATION
	// transform.setTranslation(sin_var, 0, 0);
	transform.setRotation(0, sin_var * 180, 0);
	// transform.setScale(sin_var, sin_var, sin_var);
}

void Game::render()
{
	shader.bind();
	shader.setUniform("transform", transform.getTransformation());
	mesh.draw();
}