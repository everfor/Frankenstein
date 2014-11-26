#pragma once

// Max mouse cursor shoot between frames
#define MAX_MOUSE_SHOOT			200

class Transform;

class Movement
{
	public:
		static void FreeMove(float delta, float sensitivity, Transform* transform);
		static void FreeRotate(float delta, float sensitivity, Transform* transform);
	private:
		Movement() {};
		virtual ~Movement() {};
};

