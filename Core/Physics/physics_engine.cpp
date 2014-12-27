#include "physics_engine.h"

void PhysicsEngine::update(float delta)
{
	collide(delta);
	simulate(delta);
}

void PhysicsEngine::collide(float delta)
{
}

void PhysicsEngine::simulate(float delta)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->simulate(delta);
	}
}