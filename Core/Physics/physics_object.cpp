#include "physics_object.h"
#include "core_engine.h"
#include "physics_engine.h"

void PhysicsObject::addToEngine(CoreEngine* engine)
{
	engine->getPhysicsEngine()->addObject(this);
}