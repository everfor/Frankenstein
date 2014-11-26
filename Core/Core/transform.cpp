#include "transform.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>

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
	move(getRight(), amt);
}

void Transform::moveY(float amt)
{
	move(getUp(), amt);
}

void Transform::moveZ(float amt)
{
	move(getForward(), amt);
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	setRotation(rotation * glm::angleAxis(angle, axis));
}

void Transform::rotateX(float angle)
{
	if (parent == NULL)
	{
		rotate(RIGHT_DIR, angle);
	}
	else
	{
		rotate(glm::normalize(parent->getRotation() * RIGHT_DIR), angle);
	}
}

void Transform::rotateY(float angle)
{
	if (parent == NULL)
	{
		rotate(UP_DIR, angle);
	}
	else
	{
		rotate(glm::normalize(parent->getRotation() * UP_DIR), angle);
	}
}

void Transform::rotateZ(float angle)
{
	if (parent == NULL)
	{
		rotate(FORWARD_DIR, angle);
	}
	else
	{
		rotate(glm::normalize(parent->getRotation() * FORWARD_DIR), angle);
	}
}

void Transform::compositeRotate(float x_angle, float y_anlge, float z_angle)
{
	if (parent == NULL)
	{
		setRotation(rotation * glm::angleAxis(x_angle, RIGHT_DIR)
			* glm::angleAxis(y_anlge, UP_DIR)
			* glm::angleAxis(z_angle, FORWARD_DIR));
	}
	else
	{
		setRotation(rotation * glm::angleAxis(x_angle, glm::normalize(parent->getRotation() * RIGHT_DIR))
			* glm::angleAxis(y_anlge, glm::normalize(parent->getRotation() * UP_DIR))
			* glm::angleAxis(z_angle, glm::normalize(parent->getRotation() * FORWARD_DIR)));
	}
}