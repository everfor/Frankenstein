#include "rigid_body.h"
#include "object.h"
#include "transform.h"

void RigidBody::simulate(float delta)
{
	// Velocity is always local
	getTransform()->setTranslation(getTransform()->getTranslation() + velocity * delta);
}
