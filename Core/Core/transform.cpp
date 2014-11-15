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
	updateParentTransform();

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

glm::vec3& Transform::getTransformedTranslation()
{
	updateParentTransform();
	glm::vec4 new_translation = parentTransformation * glm::vec4(translation, 1.0f);

	transformedTranslation.x = new_translation.x;
	transformedTranslation.y = new_translation.y;
	transformedTranslation.z = new_translation.z;

	return transformedTranslation;
}

glm::quat& Transform::getTransformedRotation()
{
	updateParentTransform();

	transformedRotation = glm::normalize(glm::quat(parentTransformation * glm::mat4_cast(rotation)));

	return transformedRotation;
}

glm::vec3& Transform::getTransformedScale()
{
	transformedScale.x = scale.x;
	transformedScale.y = scale.y;
	transformedScale.z = scale.z;

	if (parent != NULL)
	{
		transformedScale.x *= parent->getScale().x;
		transformedScale.y *= parent->getScale().y;
		transformedScale.z *= parent->getScale().z;
	}

	return transformedScale;
}

glm::vec3& Transform::getTransformedForward()
{
	transformedForward = glm::normalize(glm::mat3_cast(getTransformedRotation()) * FORWARD_DIR);
	
	return transformedForward;
}

glm::vec3& Transform::getTransformedBackward()
{
	transformedBackward = glm::normalize(glm::mat3_cast(getTransformedRotation()) * BACKWARD_DIR);

	return transformedBackward;
}

glm::vec3& Transform::getTransformedRight()
{
	transformedRight = glm::normalize(glm::mat3_cast(getTransformedRotation()) * RIGHT_DIR);

	return transformedRight;
}

glm::vec3& Transform::getTransformedLeft()
{
	transformedLeft = glm::normalize(glm::mat3_cast(getTransformedRotation()) * LEFT_DIR);

	return transformedLeft;
}

glm::vec3& Transform::getTransformedUp()
{
	transformedUp = glm::normalize(glm::mat3_cast(getTransformedRotation()) * UP_DIR);

	return transformedUp;
}

glm::vec3& Transform::getTransformedDown()
{
	transformedDown = glm::normalize(glm::mat3_cast(getTransformedRotation()) * DOWN_DIR);

	return transformedDown;
}


void Transform::updateParentTransform()
{
	if (parent != NULL)
	{
		parentTransformation = parent->getTransformation();
	}
}

void Transform::move(const glm::vec3& dir, float amt)
{
	setTranslation(getTranslation() + amt * glm::normalize(dir));
}

void Transform::moveX(float amt)
{
	move(getTransformedRight(), amt);
}

void Transform::moveY(float amt)
{
	move(getTransformedUp(), amt);
}

void Transform::moveZ(float amt)
{
	move(getTransformedBackward(), amt);
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	setRotation(glm::rotate(rotation, angle, glm::normalize(axis)));
}

void Transform::rotateX(float angle)
{
	rotate(getTransformedRight(), angle);
}

void Transform::rotateY(float angle)
{
	rotate(getTransformedUp(), angle);
}

void Transform::rotateZ(float angle)
{
	rotate(getTransformedForward(), angle);
}