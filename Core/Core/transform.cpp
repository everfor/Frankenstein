#include "transform.h"

#include <glm/gtx/transform.hpp>

Transform::Transform() :
			translation(glm::vec3()), rotation(glm::quat()), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
}

Transform::~Transform()
{
}

glm::mat4& Transform::getTransformation()
{
	transformation = glm::translate(translation)	// Translation
		* glm::mat4_cast(rotation)					// Rotation
		* glm::scale(scale);						// Scale

	return transformation;
}