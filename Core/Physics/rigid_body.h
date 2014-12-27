#pragma once

#include "physics_object.h"

#include <glm/glm.hpp>

class Object;

class RigidBody : public PhysicsObject
{
	public:
		RigidBody(glm::vec3& init_vel = glm::vec3()) : velocity(init_vel) {};
		virtual ~RigidBody() {};
		// Velocity
		void setVelocity(glm::vec3& new_vel) { velocity = new_vel; };
		glm::vec3& getVelocity() { return velocity; };
		// Override
		virtual void simulate(float delta) override;
	private:
		// TODO: add mass
		glm::vec3 velocity;
};

