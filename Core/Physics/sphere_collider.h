#pragma once

#include "collider.h"

class SphereCollider : public Collider
{
	public:
		SphereCollider(float init_radius) : Collider(Collider::_collider_type::COLLIDER_SPHERE), radius(init_radius) {};
		virtual ~SphereCollider();
		glm::vec3& getCenter() { return getTransform()->getTransformedTranslation(); };
		float getRadius() { return radius; };
		// Collision Detection
		Collision collideWith(Collider* other) override;
	private:
		const float radius;
};

