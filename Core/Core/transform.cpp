#include "transform.h"

#include <glm/gtx/transform.hpp>

float Transform::_fov = 0;
float Transform::_height = 0;
float Transform::_width = 0;
float Transform::_z_far = 0;
float Transform::_z_near = 0;

Transform::Transform() :
			translation(glm::vec3()), rotation(glm::vec3()), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Transform::~Transform()
{
}

glm::vec3& Transform::getTranslation()
{
	return translation;
}

void Transform::setTranslation(const glm::vec3& new_translation)
{
	translation = new_translation;
}

void Transform::setTranslation(float x, float y, float z)
{
	translation = glm::vec3(x, y, z);
}

glm::vec3& Transform::getRotation()
{
	return rotation;
}

void Transform::setRotation(const glm::vec3& new_rotation)
{
	rotation = new_rotation;
}

void Transform::setRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);
}

glm::vec3& Transform::getScale()
{
	return scale;
}

void Transform::setScale(const glm::vec3& new_scale)
{
	scale = new_scale;
}

void Transform::setScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

glm::mat4& Transform::getTransformation()
{
	transformation = glm::translate(translation)	// Translation
		* glm::rotate(rotation.z, glm::vec3(0, 0, 1)) * glm::rotate(rotation.y, glm::vec3(0, 1, 0)) * glm::rotate(rotation.x, glm::vec3(1, 0, 0))	// Rotation
		* glm::scale(scale);						// Scale

	return transformation;
}

void Transform::setProjection(float fov, float width, float height, float zNear, float zFar)
{
	_fov = fov;
	_width = width;
	_height = height;
	_z_near = zNear;
	_z_far = zFar;
}