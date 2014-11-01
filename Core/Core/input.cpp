#include "input.h"
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <bitset>

std::vector<int> Input::_KEYS(NUM_KEYS);
std::vector<int> Input::_UP_KEYS;
std::vector<int> Input::_DOWN_KEYS;

#ifdef _WIN32
#include <Windows.h>

void Input::initialize()
{
	std::fill(_KEYS.begin(), _KEYS.end(), 0x0000);
}

void Input::update()
{
	_UP_KEYS.clear();
	_DOWN_KEYS.clear();

	for (int i = 0; i < NUM_KEYS; i++)
	{
		short currentState = Input::checkKey(i);
		short stateChange = _KEYS[i] ^ currentState;

		if ((stateChange & KEY_DOWN_MASK) == KEY_DOWN_MASK)
		{
			_DOWN_KEYS.push_back(i);
		}
		else if ((stateChange & KEY_UP_MASK) == KEY_UP_MASK)
		{
			_UP_KEYS.push_back(i);
		}

		_KEYS[i] = currentState;
	}
}

bool Input::getKeyDown(int keyCode)
{
	return std::find(_DOWN_KEYS.begin(), _DOWN_KEYS.end(), keyCode) != _DOWN_KEYS.end();
}

bool Input::getKeyUp(int keyCode)
{
	return std::find(_UP_KEYS.begin(), _UP_KEYS.end(), keyCode) != _UP_KEYS.end();
}

glm::vec2 Input::getCursorPos()
{
	POINT pos;
	GetCursorPos(&pos);

	return glm::vec2(pos.x, pos.y);
}

short Input::checkKey(int keyCode)
{
	return GetKeyState(keyCode);
}

#endif