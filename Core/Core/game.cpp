#include "game.h"
#include "input.h"

#include <Windows.h>
#include <iostream>

Game::Game()
{
	Input::initialize();
}

Game::~Game()
{
}

void Game::input()
{
	if (Input::getKeyDown(MOUSE_LEFT))
	{
		std::cout << "Left mouse down!" << std::endl;
	}
	if (Input::getKeyUp(MOUSE_LEFT))
	{
		std::cout << "Left mouse up!" << std::endl;
		glm::vec2 cursor = Input::getCursorPos();
		std::cout << "x: " << cursor.x << " y: " << cursor.y << std::endl;
	}
	if (Input::getKeyDown(KEY_UP))
	{
		std::cout << "Up arrow down!" << std::endl;
	}
	if (Input::getKeyUp(KEY_UP))
	{
		std::cout << "Up arrow up!" << std::endl;
	}
	// std::cout<<Input::checkKey(VK_UP)<<std::endl;
}

void Game::update()
{
	Input::update();
}