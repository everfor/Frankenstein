#include "physics_engine.h"

PhysicsEngine::PhysicsEngine(bool if_enable_gravity) : 
				enableGravity(if_enable_gravity), gravitationalAcc(glm::vec3()),storedGravitationalAcc(glm::vec3(0.0f, 0.1f, 0.0f))
{
	if (gravityEnabled())
	{
		gravitationalAcc = storedGravitationalAcc;
	}
}

void PhysicsEngine::switchGravity(bool new_switch)
{
	enableGravity = new_switch;

	if (gravityEnabled())
	{
		gravitationalAcc = storedGravitationalAcc;
	}
}

void PhysicsEngine::setGravitationalAcc(glm::vec3& new_acc)
{
	storedGravitationalAcc = new_acc;

	if (gravityEnabled())
	{
		gravitationalAcc = storedGravitationalAcc;
	}
}

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