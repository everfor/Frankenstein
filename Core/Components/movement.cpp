#include "movement.h"
#include "input.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

void Movement::FreeMove(float delta, float sensitivity, Transform* transform)
{
	if (Input::CheckKey(KEY_DOWN) >> 15 != 0)
	{
		transform->moveZ(delta * sensitivity * -1);
	}
	else if (Input::CheckKey(KEY_UP) >> 15 != 0)
	{
		transform->moveZ(delta * sensitivity);
	}
	else if (Input::CheckKey(KEY_LEFT) >> 15 != 0)
	{
		transform->moveX(delta * sensitivity * -1);
	}
	else if (Input::CheckKey(KEY_RIGHT) >> 15 != 0)
	{
		transform->moveX(delta * sensitivity);
	}
}

void Movement::FreeRotate(float delta, float sensitivity, Transform* transform)
{
	glm::vec2 cursor_diff = Input::GetCurrentCursor() - Input::GetLastCursor();

	if (glm::length(cursor_diff) >= MAX_MOUSE_SHOOT)
	{
		return;
	}

	transform->compositeRotate(delta * (float)pow(2, sensitivity) * cursor_diff.y * -1,
								delta * (float)pow(2, sensitivity) * cursor_diff.x * -1,
								0);
}