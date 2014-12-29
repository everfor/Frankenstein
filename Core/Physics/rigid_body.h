#pragma once

#include "physics_object.h"

#include <glm/glm.hpp>

class Object;

class RigidBody : public PhysicsObject
{
	public:
		RigidBody(glm::vec3& init_vel = glm::vec3(), glm::vec3& init_acc = glm::vec3(), glm::vec3& init_ang_vel = glm::vec3(), glm::vec3& init_ang_acc = glm::vec3(),
			float init_mass = 0.0f, float init_resitution = 1.0f, float init_static_fric = 0.0f, float init_dynamic_fric = 0.0f);
		virtual ~RigidBody() {};
		// Setters
		void setMass(float new_mass) override;
		void setResitution(float new_resitution) override { resitution = new_resitution; };
		void setStaticFriction(float new_static_fric) override { static_friction = new_static_fric; };
		void setDynamicFriction(float new_dynamic_fric) override { dynamic_friction = new_dynamic_fric; };
		// Override
		virtual void setCollider(Collider* new_collider) override;
		virtual void collide(PhysicsObject *other) override;
		virtual void applyImpulse(glm::vec3& impulse, glm::vec3& contact_vector) override;
};

