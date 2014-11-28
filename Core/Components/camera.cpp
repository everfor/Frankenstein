#include "camera.h"
#include "transform.h"
#include "core_engine.h"
#include "rendering_engine.h"
#include "movement.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float init_fov, float init_asp, float init_znear, float init_zfar, float init_move_sensitivity, float init_rotate_sensitivity) :
fov(init_fov), aspect(init_asp), zNear(init_znear), zFar(init_zfar), move_sensitivity(init_move_sensitivity), rotate_sensitivity(init_rotate_sensitivity)
{
	transform_locked = false;
}

Camera::~Camera()
{
}

glm::mat4& Camera::getCameraProjection()
{
	glm::vec3 forward = glm::normalize(getTransform()->getTransformedForward());

	if (!transform_locked)
	{
		projection = glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(getTransform()->getTransformedTranslation(), getTransform()->getTransformedTranslation() + forward, UP_DIR);
	}
	else
	{
		projection = projection * glm::lookAt(getTransform()->getTransformedTranslation(), getTransform()->getTransformedTranslation() + forward, UP_DIR);
	}

	return projection;
}

void Camera::addToEngine(CoreEngine *engine)
{
	engine->getRenderingEngine()->addCamera(this);
}