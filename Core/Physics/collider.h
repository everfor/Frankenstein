#pragma once

#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>

class Collision
{	
	public:
		Collision(bool init_col = false, float init_dist = 0.0f, glm::vec3& init_normal = glm::vec3(1.0f, 0.0, 0.0)) : isColliding(init_col), distance(init_dist), collision_normal(init_normal) {};
		void setIsColliding(bool new_if_col) { isColliding = new_if_col; };
		bool ifColliding() { return isColliding; };
		float getDistance() { return distance; };
		void setDistance(float new_dist) { distance = new_dist; };
		glm::vec3& getCollisionNormal() { return collision_normal; };
		void setCollisionNormal(glm::vec3& new_normal) { collision_normal = glm::normalize(new_normal); };
	private:
		bool isColliding;
		// Distance between the center of colliders
		float distance;
		// Collision normal - direction of collision
		glm::vec3 collision_normal;
};

class Collider
{
	public:
		static enum _collider_type
		{
			COLLIDER_SPHERE,
			COLLIDER_AABB,
			COLLIDER_PLANE
		};
		Collider(_collider_type init_type) : type(init_type) {};
		virtual ~Collider() {};
		_collider_type getType() const { return type; };
		// Collision detection
		virtual Collision collideWith(Collider *other) { return Collision(); };
		// Get center
		glm::vec3& getCenter() { return getTransform()->getTransformedTranslation(); };
		void setTransform(Transform* new_transform) { transform = new_transform; };
		Transform* getTransform() { return transform; };
	private:
		const _collider_type type;
		Transform* transform;
};

