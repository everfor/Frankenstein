#pragma once

#include "object.h"
#include "physics_object.h"

#include <vector>
#include <glm/glm.hpp>

class PhysicsEngine
{
	public:
		PhysicsEngine(bool if_enable_gravity = false);
		virtual ~PhysicsEngine() {};
		void addObject(PhysicsObject* obj) { objects.push_back(obj); };
		void update(float delta);
		void switchGravity(bool new_switch);
		bool gravityEnabled() { return enableGravity; };
		void setGravitationalAcc(glm::vec3& new_acc);
		glm::vec3& getGravitationalAcc() { return gravitationalAcc; };
	private:
		// Velocity simulation
		void simulate(float delta);
		// Collision Detection
		void collide(float delta);
		std::vector<PhysicsObject*> objects;
		bool enableGravity;
		glm::vec3 gravitationalAcc;
		// Stored gravitational acceleration, just in case the user calls setter when gravity is disabled
		glm::vec3 storedGravitationalAcc;
};

