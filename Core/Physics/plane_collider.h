#pragma once

#include "collider.h"

#include <glm/glm.hpp>

class PlaneCollider : public Collider
{
	public:
		PlaneCollider(glm::vec3& init_normal) : Collider(Collider::_collider_type::COLLIDER_PLANE), normal(glm::normalize(init_normal)) {};
		virtual ~PlaneCollider();
		glm::vec3& getNormal() { return normal; };
		float getDistance() { return glm::dot(this->getTransform()->getTransformedTranslation(), normal); };
		// Override
		Collision collideWith(Collider *other) override;
	private:
		glm::vec3 normal;
		float distance;
};

