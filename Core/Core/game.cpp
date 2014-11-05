#include "game.h"
#include "input.h"
#include "vertex.h"
#include "resource_manager.h"

#include <iostream>

Game::Game() :
		mesh(Mesh()), shader(Shader())
{
	Input::Initialize();

	// TEST MESH
	Vertex vertices[3] = { Vertex(glm::vec3(-1, -1, 0)), Vertex(glm::vec3(0, 1, 0)), Vertex(glm::vec3(1, -1, 0)) };
	mesh.addVertices(vertices, sizeof(vertices) / sizeof(vertices[0]));

	// TEST SHADER
	shader.addVertexShader(ResourceManager::LoadShader("./res/shaders/basicShader.vs"));
	// shader.addFragmentShader(ResourceManager::LoadShader("./res/shaders/basicShader.fs"));
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
	// std::cout<<Input::checkKey(VK_UP)<<std::endl;
}

void Game::update()
{
	Input::Update();
}

void Game::render()
{
	shader.bind();
	mesh.draw();
}