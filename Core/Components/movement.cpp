#include "movement.h"
#include "input.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

void Movement::input(Transform *transform, float delta)
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