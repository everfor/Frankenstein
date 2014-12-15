#include "sphere_collider.h"

Collision SphereCollider::collideWith(Collider* other)
{
	Collider::_collider_type other_type = other->getType();
	Collision collision;

	if (other_type == Collider::_collider_type::COLLIDER_SPHERE)
	{
		float radiusDist = radius + ((SphereCollider*)other)->getRadius();
		glm::vec3 centerDir = ((SphereCollider*)other)->getCenter() - getCenter();
		float centerDist = glm::length(centerDir);
		centerDir = centerDir / centerDist;

		// Set collision data
		collision.setDirection(centerDir);
		collision.setDistance(centerDist);
		if (centerDist < radiusDist)
		{
			collision.setIsColliding(true);
		}
	}

	return collision;
}