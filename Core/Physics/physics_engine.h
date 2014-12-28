#pragma once

#include "object.h"
#include "physics_object.h"

#include <vector>

class PhysicsEngine
{
	public:
		PhysicsEngine() {};
		virtual ~PhysicsEngine() {};
		void addObject(PhysicsObject* obj) { objects.push_back(obj); };
		void update(float delta);
	private:
		// Velocity simulation
		void simulate(float delta);
		// Collision Detection
		void collide(float delta);
		std::vector<PhysicsObject*> objects;
};

