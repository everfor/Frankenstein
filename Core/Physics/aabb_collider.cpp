#include "aabb_collider.h"

#include <cmath>

Collision AABBCollider::collideWith(Collider* other)
{
	Collider::_collider_type other_type = other->getType();
	Collision collision;

	if (other_type == Collider::_collider_type::COLLIDER_AABB)
	{
		glm::vec3 centerDir  = other->getCenter() - getCenter();
		float centerDist = glm::length(centerDir);
		centerDir = centerDir / centerDist;

		collision.setDistance(centerDist);

		glm::vec3 dist1 = ((AABBCollider*)other)->getMinExtents() - getMaxExtents();
		glm::vec3 dist2 = getMinExtents() - ((AABBCollider*)other)->getMaxExtents();

		glm::vec3 normal = glm::vec3(fmaxf(dist1.x, dist2.x), fmaxf(dist1.y, dist2.y), fmaxf(dist1.z, dist2.z));
		collision.setCollisionNormal(normal);

		// Get largest components from the two calculated distances
		float maxDist = fmaxf(fmaxf(normal.x, normal.y), normal.z);

		// Collision Detection
		collision.setIsColliding(maxDist < 0);
	}

	return collision;
}