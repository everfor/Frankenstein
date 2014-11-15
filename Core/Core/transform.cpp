#include "transform.h"

#include <glm/gtx/transform.hpp>

Transform::Transform() :
parent(NULL), translation(glm::vec3()), rotation(glm::quat()), scale(glm::vec3(1.0f, 1.0f, 1.0f)), isTransformationChanged(true)
{
	// Initialize a parent unit transform
	parentTransformation = glm::translate(glm::vec3()) * glm::mat4_cast(glm::quat()) * glm::scale(glm::vec3(1, 1, 1));
}

Transform::~Transform()
{
}

glm::mat4& Transform::getTransformation()
{
	if (parent != NULL)
	{
		parentTransformation = parent->getTransformation();
	}

	if (isChanged())
	{
		transformation = parentTransformation			// Parent
			* glm::translate(translation)				// Translation
			* glm::mat4_cast(rotation)					// Rotation
			* glm::scale(scale);						// Scale
	}
	else
	{
		transformation = parentTransformation * transformation;
	}

	return transformation;
}