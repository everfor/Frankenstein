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

void Camera::move(const glm::vec3& dir, float amt)
{
	getTransform()->setTranslation(getTransform()->getTranslation() + amt * glm::normalize(dir));
}

void Camera::moveX(float amt)
{
	move(getTransform()->getRight(), amt);
}

void Camera::moveY(float amt)
{
	move(getTransform()->getUp(), amt);
}

void Camera::moveZ(float amt)
{
	move(getTransform()->getBackward(), amt);
}

glm::mat4& Camera::getCameraProjection()
{
	glm::vec3 forward = glm::normalize(getTransform()->getForward());
	projection = glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(getTransform()->getTranslation(), getTransform()->getTranslation() + forward, UP_DIR);

	return projection;
}

void Camera::addToRenderingEngine(RenderingEngine *engine)
{
	engine->addCamera(this);
}