#pragma once

#include <vector>
#include <glm/glm.hpp>

#ifdef _WIN32
#define UP_UNTOGGELED		0x0000
#define UP_TOGGLED			0x0001
#define DONW_UNTOGGLED		0x8000
#define DOWN_TOGGLED		0x8001

#define KEY_DOWN_MASK		0x8001
#define KEY_UP_MASK			0x8000
#endif

#define NUM_KEYS			256
/*
 * Handles different kinds of input
*/
class Input
{
	public:
		static void initialize();
		static void update();
		static bool getKeyDown(int keyCode);
		static bool getKeyUp(int keyCode);
		static glm::vec2 getCursorPos();
	private:
		static std::vector<int> _KEYS;
		static std::vector<int>	_UP_KEYS;
		static std::vector<int> _DOWN_KEYS;
		static short checkKey(int keyCode);
};
