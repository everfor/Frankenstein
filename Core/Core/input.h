#pragma once

#include <vector>
#include <glm/glm.hpp>

#ifdef _WIN32
#include <Windows.h>
// Key States
#define UP_UNTOGGELED		0x0000
#define UP_TOGGLED			0x0001
#define DONW_UNTOGGLED		0x8000
#define DOWN_TOGGLED		0x8001
// Key State Change Detection
#define KEY_DOWN_MASK		0x8001
#define KEY_UP_MASK			0x8000
// Key Codes - Generic ones so they are platform-independent
// Format:
// KEY_ : Keys in main keyboard
// NUM_ : Keys in num pad
// MOUSE_ : Mouse keys
#define MOUSE_LEFT			VK_LBUTTON
#define MOUSE_RIGHT			VK_RBUTTON
#define MOUSE_MIDDLE		VK_MBUTTON
#define MOUSE_X1			VK_XBUTTON1
#define MOUSE_X2			VK_XBUTTON2
#define KEY_CANCEL			VK_CANCEL
#define KEY_BACKSPACE		VK_BACK
#define KEY_TAB				VK_TAB
#define KEY_CLEAR			VK_CLEAR
#define KEY_SHIFT			VK_SHIFT
#define KEY_CONTROL			VK_CONTROL
#define KEY_ALT				VK_MENU
#define KEY_PAUSE			VK_PAUSE
#define KEY_CAPSLOCK		VK_CAPITAL
#define KEY_ESC				VK_ESCAPE
#define KEY_SPACE			VK_SPACE
#define KEY_PAGEUP			VK_PRIOR
#define KEY_PAGEDOWN		VK_NEXT
#define KEY_END				VK_END
#define KEY_HOME			VK_HOME
#define KEY_LEFT			VK_LEFT
#define KEY_UP				VK_UP
#define KEY_DOWN			VK_DOWN
#define KEY_LEFT			VK_LEFT
#define KEY_SELECT			VK_SELECT
#define KEY_PRINT			VK_PRINT
#define KEY_EXEC			VK_EXECUTE
#define KEY_PRINTSCREEN		VK_SNAPSHOT
#define KEY_INSERT			VK_INSERT
#define KEY_DELETE			VK_DELETE
#define KEY_HELP			VK_HELP
#define KEY_0				0x30
#define KEY_1				0x31
#define KEY_2				0x32
#define KEY_3				0x33
#define KEY_4				0x34
#define KEY_5				0x35
#define KEY_6				0x36
#define KEY_7				0x37
#define KEY_8				0x38
#define KEY_9				0x39
#define KEY_A				0x41
#define KEY_B				0x42
#define KEY_C				0x43
#define KEY_D				0x44
#define KEY_E				0x45
#define KEY_F				0x46
#define KEY_G				0x47
#define KEY_H				0x48
#define KEY_I				0x49
#define KEY_J				0x4A
#define KEY_K				0x4B
#define KEY_L				0x4C
#define KEY_M				0x4D
#define KEY_N				0x4E
#define KEY_O				0x4F
#define KEY_P				0x50
#define KEY_Q				0x51
#define KEY_R				0x52
#define KEY_S				0x53
#define KEY_T				0x54
#define KEY_U				0x55
#define KEY_V				0x56
#define KEY_W				0x57
#define KEY_X				0x58
#define KEY_Y				0x59
#define KEY_Z				0x5A
#define KEY_LWIN			VK_LWIN
#define KEY_RWIN			VK_RWIN
#define KEY_APPLICATION		VK_APPS
#define KEY_SLEEP			VK_SLEEP
#define KEY_F1				VK_F1
#define KEY_F2				VK_F2
#define KEY_F3				VK_F3
#define KEY_F4				VK_F4
#define KEY_F5				VK_F5
#define KEY_F6				VK_F6
#define KEY_F7				VK_F7
#define KEY_F8				VK_F8
#define KEY_F9				VK_F9
#define KEY_F10				VK_F10
#define KEY_F11				VK_F11
#define KEY_F12				VK_F12
#define KEY_F13				VK_F13
#define KEY_F14				VK_F14
#define KEY_F15				VK_F15
#define KEY_F16				VK_F16
#define KEY_F17				VK_F17
#define KEY_F18				VK_F18
#define KEY_F19				VK_F19
#define KEY_F20				VK_F20
#define KEY_F21				VK_F21
#define KEY_F22				VK_F22
#define KEY_F23				VK_F23
#define KEY_F24				VK_F24
#define KEY_NUMLOCK			VK_NUMLOCK
#define KEY_SCROLLLOCK		VK_SCROLL
#define KEY_LSHIFT			VK_LSHIFT
#define KEY_RSHIFT			VK_RSHIFT
#define KEY_LCONTROL		VK_LCONTROL
#define KEY_RCONTROL		VK_RCONTROL
#define KEY_LMENU			VK_LMENU
#define KEY_RMENU			VK_RMENU
#define KEY_COMMA			VK_OEM_COMMA
#define KEY_MINUS			VK_OEM_MINUS
#define KEY_PLUS			VK_OEM_PLUS
#define KEY_PERIOD			VK_OEM_PERIOD
#define KEY_GENERAL_1		VK_OEM_1		// ";:" key for US keyboard
#define KEY_GENERAL_2		VK_OEM_2		// "/?" key for US keyboard
#define KEY_GENERAL_3		VK_OEM_3		// "~" key for US keyboard
#define KEY_GENERAL_4		VK_OEM_4		// "[{" key for US keyboard
#define KEY_GENERAL_5		VK_OEM_5		// "\|" key for US keyboard
#define KEY_GENERAL_6		VK_OEM_6		// "]}" key for US keyboard
#define KEY_GENERAL_7		VK_OEM_7		// "'"" key for US keyboard
#define KEY_GENERAL_8		VK_OEM_8
#define NUM_0				VK_NUMPAD0
#define NUM_1				VK_NUMPAD1
#define NUM_2				VK_NUMPAD2
#define NUM_3				VK_NUMPAD3
#define NUM_4				VK_NUMPAD4
#define NUM_5				VK_NUMPAD5
#define NUM_6				VK_NUMPAD6
#define NUM_7				VK_NUMPAD7
#define NUM_8				VK_NUMPAD8
#define NUM_9				VK_NUMPAD9
#define NUM_ADD				VK_ADD
#define NUM_SUBTRACT		VK_SUBTRACT
#define NUM_MULTIPLY		VK_MULTIPLY
#define NUM_DIVIDE			VK_DIVIDE
#define NUM_SEPARATOR		VK_SEPARATOR
#define NUM_DECIMAL			VK_DECIMAL
#endif

#define TOTAL_KEYS			256
/*
 * Handles different kinds of input
*/
class Input
{
	public:
		static void Initialize();
		static void Update();
		static bool GetKeyDown(int keyCode);
		static bool GetKeyUp(int keyCode);
		static glm::vec2 GetCursorPosition();
	private:
		Input();
		~Input();
		static std::vector<int> _KEYS;
		static std::vector<int>	_UP_KEYS;
		static std::vector<int> _DOWN_KEYS;
		static short CheckKey(int keyCode);
};
