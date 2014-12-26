#pragma once

#include "component.h"

#include <glm/glm.hpp>

class Object;

class RigidBody : public Component
{
	public:
		RigidBody(glm::vec3& init_vel = glm::vec3()) : velocity(init_vel) {};
		virtual ~RigidBody() {};
		void update(Transform *transform, float delta) override;
		void acceptParentObj(Object* obj) override;
		// Velocity
		void setVelocity(glm::vec3& new_vel) { velocity = new_vel; };
		glm::vec3& getVelocity() { return velocity; };
	private:
		// TODO: add mass
		glm::vec3 velocity;
};

