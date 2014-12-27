#include "physics_object.h"
#include "core_engine.h"
#include "physics_engine.h"

PhysicsObject::PhysicsObject(_physobj_type init_type, Collider* init_collider) : 
			velocity(glm::vec3()), mass(0.0f), inv_mass(0.0f), resitution(1.0f),
			collider(std::unique_ptr<Collider>(init_collider)), type(init_type)
{
	if (collider.get() != NULL)
	{
		collider.get()->setTransform(getTransform());
	}
}

void PhysicsObject::addToEngine(CoreEngine* engine)
{
	engine->getPhysicsEngine()->addObject(this);
}

void PhysicsObject::setCollider(Collider *new_collider)
{
	collider.reset(new_collider);

	if (new_collider != NULL)
	{
		collider.get()->setTransform(getTransform());
	}
}

void PhysicsObject::setTransform(Transform* new_transform)
{
	Component::setTransform(new_transform);

	if (collider.get() != NULL)
	{
		collider.get()->setTransform(getTransform());
	}
}