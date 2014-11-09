#include "camera.h"

#include <glm/gtx/transform.hpp>

const glm::vec3 Camera::_X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Camera::_Y_AXIS = glm::vec3(0, 1, 0);
const glm::vec3 Camera::_Z_AXIS = glm::vec3(0, 0, 1);
const glm::vec3 Camera::_FORWARD_DIR = glm::vec3(0, 0, 1);
const glm::vec3 Camera::_UP_DIR = glm::vec3(0, 1, 0);

Camera::Camera(float init_fov, float init_asp, float init_znear, float init_zfar, glm::vec3& init_pos, glm::quat& init_orient) :
			position(init_pos), orientation(glm::normalize(init_orient)), fov(init_fov), aspect(init_asp), zNear(init_znear), zFar(init_zfar)
{
}

Camera::~Camera()
{
}

void Camera::move(glm::vec3& dir, float amt)
{
	position += amt * glm::normalize(dir);
}

void Camera::rotate(const glm::vec3& axis, float angle)
{
	orientation = glm::rotate(orientation, angle, glm::normalize(axis));
}

void Camera::rotateX(float angle)
{
	rotate(_X_AXIS, angle);
}

void Camera::rotateY(float angle)
{
	rotate(_Y_AXIS, angle);
}

void Camera::rotateZ(float angle)
{
	rotate(_Z_AXIS, angle);
}

glm::mat4& Camera::getCameraProjection()
{
	glm::vec3 forward = glm::normalize(glm::mat3_cast(orientation) * _FORWARD_DIR);
	projection = glm::perspective(fov, aspect, zNear, zFar) * glm::lookAt(position, position + forward, _UP_DIR);

	return projection;
}