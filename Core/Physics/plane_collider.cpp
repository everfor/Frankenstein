#include "plane_collider.h"
#include "sphere_collider.h"

Collision PlaneCollider::collideWith(Collider *other)
{
	Collider::_collider_type other_type = other->getType();
	Collision collision;

	collision.setImpactPoint((other->getCenter() + getCenter()) / 2.0f);

	if (other_type == Collider::_collider_type::COLLIDER_SPHERE)
	{
		// Sphere center distance + distance of the plane from origin
		float sphereCenterDist = glm::dot(other->getCenter(), normal) - getDistance();
		float sphereDist = fabs(sphereCenterDist) - ((SphereCollider*)other)->getRadius();

		glm::vec3 centerDir = normal * sphereCenterDist;

		collision.setIsColliding(sphereDist > 0);
		collision.setPenetration(fabs(sphereDist));
		collision.setCollisionNormal(getNormal());
	}

	return collision;
}
