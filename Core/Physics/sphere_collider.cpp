#include "sphere_collider.h"
#include "plane_collider.h"
#include "aabb_collider.h"

#include <iostream>

Collision SphereCollider::collideWith(Collider* other)
{
	Collider::_collider_type other_type = other->getType();
	Collision collision;

	if (other_type == Collider::_collider_type::COLLIDER_SPHERE)
	{
		float radiusDist = radius + ((SphereCollider*)other)->getRadius();
		glm::vec3 centerDir = other->getCenter() - getCenter();
		float centerDist = glm::length(centerDir);
		centerDir = centerDir / centerDist;
		float penetration = radiusDist - centerDist;

		// Set collision data
		collision.setCollisionNormal(centerDir);
		collision.setPenetration(penetration);
		collision.setContactRadiusA((getRadius() - penetration) * centerDir);
		collision.setContactRadiusB((((SphereCollider*)other)->getRadius() - penetration) * centerDir);

		// Collision Detection
		collision.setIsColliding(centerDist < radiusDist);
	}
	else if (other_type == Collider::_collider_type::COLLIDER_AABB)
	{
		glm::vec3 center = getCenter();

		glm::vec3 other_min_extents = ((AABBCollider*)other)->getMinExtents();
		glm::vec3 other_max_extents = ((AABBCollider*)other)->getMaxExtents();

		glm::vec3 normal = other->getCenter() - center;

		glm::vec3 dist1 = other_min_extents - center;
		glm::vec3 dist2 = other_max_extents - center;

		// Distance between the center of sphere and the closest corner of aabb
		glm::vec3 min_dist = glm::vec3(fminf(fabs(dist1.x), fabs(dist2.x)), fminf(fabs(dist1.y), fabs(dist2.y)), fminf(fabs(dist1.z), fabs(dist2.z)));

		// If sphere is inside aabb
		if (center.x > other_min_extents.x && center.x < other_max_extents.x
			&& center.y > other_min_extents.y && center.y < other_max_extents.y
			&& center.z > other_min_extents.z && center.z < other_max_extents.z)
		{
			collision.setIsColliding(true);
			collision.setCollisionNormal(normal);
			collision.setPenetration(glm::length(min_dist));
		}
		else
		{
			// Sphere is outside or on the edge of aabb
			collision.setIsColliding(getRadius() > glm::length(min_dist));
			collision.setCollisionNormal(normal);
			collision.setPenetration(getRadius() - glm::length(min_dist));
		}
	}
	else if (other_type == Collider::_collider_type::COLLIDER_PLANE)
	{
		float sphereCenterDist = glm::dot(getCenter(), ((PlaneCollider*)other)->getNormal()) - ((PlaneCollider*)other)->getDistance();
		float sphereDist = fabs(sphereCenterDist) - getRadius();

		collision.setIsColliding(sphereDist < 0);
		collision.setPenetration(fabs(sphereDist));
		collision.setCollisionNormal(((PlaneCollider*)other)->getNormal());
	}

	return collision;
}