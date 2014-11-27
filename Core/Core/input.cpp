#include "input.h"
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <bitset>

std::vector<int> Input::_KEYS(TOTAL_KEYS);
std::vector<int> Input::_UP_KEYS;
std::vector<int> Input::_DOWN_KEYS;
glm::vec2 Input::_last_cursor_pos = glm::vec2(0, 0);
glm::vec2 Input::_current_cursor_pos = glm::vec2(0, 0);

#ifdef _WIN32
#include <Windows.h>

void Input::Initialize()
{
	std::fill(_KEYS.begin(), _KEYS.end(), 0x0000);
	Input::_UP_KEYS.reserve(TOTAL_KEYS);
	Input::_DOWN_KEYS.reserve(TOTAL_KEYS);
}

void Input::Update()
{
	_UP_KEYS.clear();
	_DOWN_KEYS.clear();

	for (int i = 0; i < TOTAL_KEYS; i++)
	{
		short currentState = Input::CheckKey(i);
		short stateChange = _KEYS[i] ^ currentState;

		if ((stateChange & KEY_TOGGLE_DOWN_MASK) == KEY_TOGGLE_DOWN_MASK)
		{
			_DOWN_KEYS.push_back(i);
		}
		else if ((stateChange & KEY_TOGGLE_UP_MASK) == KEY_TOGGLE_UP_MASK)
		{
			_UP_KEYS.push_back(i);
		}

		_KEYS[i] = currentState;
	}

	_last_cursor_pos = _current_cursor_pos;
	_current_cursor_pos = GetCursorPosition();
}

bool Input::GetKeyDown(int keyCode)
{
	return std::find(_DOWN_KEYS.begin(), _DOWN_KEYS.end(), keyCode) != _DOWN_KEYS.end();
}

bool Input::GetKeyUp(int keyCode)
{
	return std::find(_UP_KEYS.begin(), _UP_KEYS.end(), keyCode) != _UP_KEYS.end();
}

glm::vec2 Input::GetCursorPosition()
{
	POINT pos;
	GetCursorPos(&pos);

	return glm::vec2(pos.x, pos.y);
}

short Input::CheckKey(int keyCode)
{
	return GetKeyState(keyCode);
}

#endif