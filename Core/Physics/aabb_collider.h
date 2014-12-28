#pragma once

#include "collider.h"

#include <glm/glm.hpp>

class AABBCollider : public Collider
{
	public:
		AABBCollider(glm::vec3& init_min, glm::vec3& init_max) : 
			Collider(Collider::_collider_type::COLLIDER_AABB), min_relative_extents(init_min), max_relative_extents(init_max)
		{};
		virtual ~AABBCollider() {};
		glm::vec3& getMinExtents() { min_extents = getTransform()->getTransformedTranslation() + min_relative_extents ; return min_extents; };
		glm::vec3& getMaxExtents() { max_extents = getTransform()->getTransformedTranslation() + max_relative_extents; return max_extents; };
		// Collision Detection
		Collision collideWith(Collider* other) override;
	private:
		// lower left corner
		glm::vec3 min_relative_extents;
		glm::vec3 min_extents;
		// upper right corner
		glm::vec3 max_relative_extents;
		glm::vec3 max_extents;
};

