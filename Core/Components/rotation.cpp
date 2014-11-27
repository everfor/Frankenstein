#include "rotation.h"
#include "input.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

void Rotation::input(Transform *transform, float delta)
{
	glm::vec2 cursor_diff = Input::GetCurrentCursor() - Input::GetLastCursor();

	if (glm::length(cursor_diff) >= MAX_MOUSE_SHOOT)
	{
		return;
	}

	transform->rotateX(delta * (float)pow(2, sensitivity) * cursor_diff.y * -1);
	transform->rotate(transform->getUp(), delta * (float)pow(2, sensitivity) * cursor_diff.x * -1);
}