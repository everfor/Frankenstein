#include "aabb_collider.h"
#include "plane_collider.h"
#include "sphere_collider.h"

#include <cmath>

Collision AABBCollider::collideWith(Collider* other)
{
	Collider::_collider_type other_type = other->getType();
	Collision collision;

	// Set impact point
	collision.setImpactPoint((other->getCenter() + getCenter()) / 2.0f);

	if (other_type == Collider::_collider_type::COLLIDER_AABB)
	{
		// Collision normal is the relative direction between the two aabbs
		glm::vec3 normal = other->getCenter() - getCenter();

		glm::vec3 dist1 = ((AABBCollider*)other)->getMinExtents() - getMaxExtents();
		glm::vec3 dist2 = getMinExtents() - ((AABBCollider*)other)->getMaxExtents();

		glm::vec3 max_dist = glm::vec3(fmaxf(dist1.x, dist2.x), fmaxf(dist1.y, dist2.y), fmaxf(dist1.z, dist2.z));

		// Get largest components from the two calculated distances
		float maxDist = fmaxf(fmaxf(max_dist.x, max_dist.y), max_dist.z);
		// Collision Detection
		collision.setIsColliding(maxDist < 0);

		collision.setCollisionNormal(normal);
		collision.setPenetration(glm::length(max_dist));
	}
	else if (other_type == Collider::_collider_type::COLLIDER_SPHERE)
	{
		glm::vec3 max_extents = getMaxExtents();
		glm::vec3 min_extents = getMinExtents();

		glm::vec3 other_center = other->getCenter();

		glm::vec3 normal = other_center - getCenter();

		glm::vec3 dist1 = other_center - min_extents;
		glm::vec3 dist2 = other_center - max_extents;

		// Distance between the center of sphere and the closest corner of aabb
		glm::vec3 min_dist = glm::vec3(fminf(fabs(dist1.x), fabs(dist2.x)), fminf(fabs(dist1.y), fabs(dist2.y)), fminf(fabs(dist1.z), fabs(dist2.z)));

		// If the sphere is inside aabb
		if (other_center.x > min_extents.x && other_center.x < max_extents.x
			&& other_center.y > min_extents.y && other_center.y < max_extents.y
			&& other_center.z > min_extents.z && other_center.z < max_extents.z)
		{
			collision.setIsColliding(true);
			collision.setCollisionNormal(normal);
			collision.setPenetration(glm::length(min_dist));
		}
		else
		{
			// Sphere is outside or on the edge of the aabb
			collision.setIsColliding(((SphereCollider*)other)->getRadius() > glm::length(min_dist));
			collision.setCollisionNormal(normal);
			collision.setPenetration(((SphereCollider*)other)->getRadius() - glm::length(min_dist));
		}
	}
	else if (other_type == Collider::_collider_type::COLLIDER_PLANE)
	{

	}

	return collision;
}