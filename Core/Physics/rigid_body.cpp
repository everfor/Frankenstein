#include "rigid_body.h"
#include "object.h"
#include "transform.h"

RigidBody::RigidBody(glm::vec3& init_vel, float init_mass, float init_resitution) : 
			PhysicsObject(PhysicsObject::_physobj_type::TYPE_RIGID_BODY)
{
	setVelocity(init_vel);
	setMass(init_mass);
	setResitution(init_resitution);
}

void RigidBody::setMass(float new_mass)
{
	float new_inv_mass;

	// 0.0 is infinite mass
	if (new_mass == 0.0f)
	{
		new_inv_mass = 0.0f;
	}
	else
	{
		new_inv_mass = 1.0f / new_mass;
	}

	mass = new_mass;
	inv_mass = new_inv_mass;
}

void RigidBody::simulate(float delta)
{
	// Velocity is always local
	getTransform()->setTranslation(getTransform()->getTranslation() + velocity * delta);
}

void RigidBody::collide(PhysicsObject *other)
{
	// Make sure we are now colliding with a null
	if (other != NULL)
	{
		// Make sure both have colliders
		if (getCollider() != NULL && other->getCollider() != NULL)
		{
			// Only collide if two objects share same layers
			if (getLayer() & other->getLayer() != 0)
			{
				Collision collision = getCollider()->collideWith(other->getCollider());

				// Only calculate impulse when actually colliding
				if (collision.ifColliding())
				{
					// collide - impulse resolution

					// Get the resitution for this collision
					float collision_resitution = fminf(getRestitution(), other->getRestitution());

					float velocity_along_normal = glm::dot(getVelocity() - other->getVelocity(), collision.getCollisionNormal());

					// Calculate impulse
					float impulse = (1 + collision_resitution) * velocity_along_normal / (getInvMass() + other->getInvMass());

					// Modify velocity
					setVelocity(getVelocity() - impulse * getInvMass() * collision.getCollisionNormal());
					other->setVelocity(other->getVelocity() + impulse * other->getInvMass() * collision.getCollisionNormal());
				}
			}
		}
	}
}