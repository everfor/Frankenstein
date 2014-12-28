#include "physics_engine.h"

void PhysicsEngine::update(float delta)
{
	collide(delta);
	simulate(delta);
}

void PhysicsEngine::collide(float delta)
{
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			objects[i]->collide(objects[j]);
		}
	}
}

void PhysicsEngine::simulate(float delta)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->simulate(delta);
	}
}