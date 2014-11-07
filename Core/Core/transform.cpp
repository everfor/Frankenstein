#include "transform.h"

#include <glm/gtx/transform.hpp>

Transform::Transform() :
			translation(glm::vec3())
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

glm::mat4& Transform::getTransformation()
{
	glm::mat4 trans = glm::translate(translation);

	transformation = trans;

	return transformation;
}