#include "rigid_body.h"
#include "object.h"
#include "transform.h"

void RigidBody::update(Transform *transform, float delta)
{
	// Velocity is always local
	transform->setTranslation(transform->getTranslation() + velocity * delta);
}

void RigidBody::acceptParentObj(Object *obj)
{
	obj->setHasRigidBody(true);
}
