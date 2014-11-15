#include "camera.h"
#include "transform.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float init_fov, float init_asp, float init_znear, float init_zfar, glm::vec3& init_pos, glm::quat& init_orient) :
			position(init_pos), orientation(glm::normalize(init_orient)), fov(init_fov), aspect(init_asp), zNear(init_znear), zFar(init_zfar)
{
}

Camera::~Camera()
{
}

void Camera::move(const glm::vec3& dir, float amt)
{
	position += amt * glm::normalize(dir);
}

void Camera::moveX(float amt)
{
	move(X_AXIS, amt);
}

void Camera::moveY(float amt)
{
	move(Y_AXIS, amt);
}

void Camera::moveZ(float amt)
{
	move(Z_AXIS, amt);
}

void Camera::rotate(const glm::vec3& axis, float angle)
{
	orientation = glm::rotate(orientation, angle, glm::normalize(axis));
}

void Camera::rotateX(float angle)
{
	rotate(X_AXIS, angle);
}

void Camera::rotateY(float angle)
{
	rotate(Y_AXIS, angle);
}

void Camera::rotateZ(float angle)
{
	rotate(Z_AXIS, angle);
}

glm::mat4& Camera::getCameraProjection()
{
	glm::vec3 forward = glm::normalize(glm::mat3_cast(orientation) * FORWARD_DIR);
	projection = glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(position, position + forward, UP_DIR);

	return projection;
}