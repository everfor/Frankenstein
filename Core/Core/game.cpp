#include "game.h"
#include "input.h"
#include "vertex.h"

#include <iostream>

Game::Game() :
		mesh(Mesh())
{
	Input::Initialize();

	// TEST MESH
	Vertex vertices[] = {Vertex(glm::vec3(-1.0f, 1.0f, 0.0f)), Vertex(glm::vec3(0.0f, 1.0f, 0.0f)), Vertex(glm::vec3(-1.0f, 1.0f, 0.0f))};
	mesh.addVertices(vertices, 3);
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
	mesh.draw();
}