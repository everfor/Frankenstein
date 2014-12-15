#pragma once

#include "component.h"

#include <glm/glm.hpp>

class Collision
{	
	public:
		Collision(bool init_col = false, float init_dist = 0.0f, glm::vec3& init_dir = glm::vec3()) : isColliding(init_col), distance(init_dist), direction(init_dir) {};
		void setIsColliding(bool new_if_col) { isColliding = new_if_col; };
		bool ifColliding() { return isColliding; };
		float getDistance() { return distance; };
		void setDistance(float new_dist) { distance = new_dist; };
		glm::vec3& getDirection() { return direction; };
		void setDirection(glm::vec3& new_dir) { direction = new_dir; };
	private:
		bool isColliding;
		// Distance between the center of colliders
		float distance;
		// Direction of the center of one collider to another
		glm::vec3 direction;
};

class Collider : public Component
{
	public:
		static enum _collider_type
		{
			COLLIDER_SPHERE,
			COLLIDER_AABB
		};
		Collider(_collider_type init_type) : type(init_type) {};
		virtual ~Collider() {};
		_collider_type getType() const { return type; };
		// Collision detection
		virtual Collision collideWith(Collider *other) { return Collision(); };
	private:
		const _collider_type type;
};

