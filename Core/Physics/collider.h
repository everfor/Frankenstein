#pragma once

#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>

class Collision
{	
	public:
		Collision(bool init_col = false, float init_pene = 0.0f, glm::vec3& init_normal = glm::vec3(1.0f, 0.0, 0.0)) : 
			isColliding(init_col), penetration(init_pene), collision_normal(init_normal), contact_radius_a(glm::vec3()), contact_radius_b(glm::vec3())
		{};
		void setIsColliding(bool new_if_col) { isColliding = new_if_col; };
		bool ifColliding() { return isColliding; };
		float getPenetration() { return penetration; };
		void setPenetration(float new_pene) { penetration = new_pene; };
		glm::vec3& getCollisionNormal() { return collision_normal; };
		void setCollisionNormal(glm::vec3& new_normal) { collision_normal = glm::normalize(new_normal); };
		glm::vec3& getContactRadiusA() { return contact_radius_a; };
		void setContactRadiusA(glm::vec3 new_a) { contact_radius_a = new_a; };
		glm::vec3& getContactRadiusB() { return contact_radius_b; };
		void setContactRadiusB(glm::vec3 new_b) { contact_radius_b = new_b; };
	private:
		bool isColliding;
		// Depth of penetration
		float penetration;
		// Collision normal - direction of collision
		glm::vec3 collision_normal;
		// Contact radii
		glm::vec3 contact_radius_a;
		glm::vec3 contact_radius_b;
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

