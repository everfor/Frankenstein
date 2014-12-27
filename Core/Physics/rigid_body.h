#pragma once

#include "physics_object.h"

#include <glm/glm.hpp>

class Object;

class RigidBody : public PhysicsObject
{
	public:
		RigidBody(glm::vec3& init_vel = glm::vec3(), float init_mass = 0.0f, float init_resitution = 1.0f);
		virtual ~RigidBody() {};
		// Setters
		void setVelocity(glm::vec3& new_vel) override { velocity = new_vel; };
		void setMass(float new_mass) override;
		void setResitution(float new_resitution) override { resitution = new_resitution; };
		// Override
		virtual void simulate(float delta) override;
		virtual void collide(PhysicsObject *other) override;
};

