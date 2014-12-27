#pragma once

#include "component.h"
#include "collider.h"

#include <memory>
#include <glm/glm.hpp>

class CoreEngine;

class PhysicsObject : public Component
{
	public:
		static enum _physobj_type
		{
			TYPE_GENERAL,
			TYPE_RIGID_BODY
		};
		PhysicsObject(_physobj_type init_type = _physobj_type::TYPE_GENERAL, Collider* init_collider = NULL);
		virtual ~PhysicsObject() {};
		void setCollider(Collider* new_collider);
		Collider* getCollider() { return collider.get(); };
		_physobj_type getType() { return type; };
		// Used for update in physics engine
		virtual void simulate(float delta) {};
		virtual void collide(PhysicsObject *other) {};
		virtual void addToEngine(CoreEngine* engine);
		// Getters for some members - they are immutable for general phys objects
		glm::vec3& getVelocity() { return velocity; };
		float getMass() { return mass; };
		float getInvMass() { return inv_mass; };
		float getRestitution() { return resitution; };
		// Override
		virtual void setTransform(Transform *new_transform) override;
		// Setters
		virtual void setVelocity(glm::vec3& new_vel) {};
		virtual void setMass(float new_mass) {};
		virtual void setResitution(float new_resitution) {};
	protected:
		glm::vec3 velocity;
		float mass;
		float inv_mass;
		float resitution;
	private:
		std::unique_ptr<Collider> collider;
		_physobj_type type;
};

