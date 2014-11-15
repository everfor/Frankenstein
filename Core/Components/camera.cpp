#include "camera.h"
#include "transform.h"
#include "rendering_engine.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float init_fov, float init_asp, float init_znear, float init_zfar) :
			fov(init_fov), aspect(init_asp), zNear(init_znear), zFar(init_zfar)
{
}

Camera::~Camera()
{
}

glm::mat4& Camera::getCameraProjection()
{
	glm::vec3 forward = glm::normalize(getTransform()->getTransformedForward());
	projection = glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(getTransform()->getTransformedTranslation(), getTransform()->getTransformedTranslation() + forward, UP_DIR);

	return projection;
}

void Camera::addToRenderingEngine(RenderingEngine *engine)
{
	engine->addCamera(this);
}