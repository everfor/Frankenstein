#include "rigid_body.h"
#include "object.h"
#include "transform.h"

RigidBody::RigidBody(glm::vec3& init_vel, float init_mass, float init_resitution, float init_static_fric, float init_dynamic_fric) :
			PhysicsObject(PhysicsObject::_physobj_type::TYPE_RIGID_BODY)
{
	setVelocity(init_vel);
	setMass(init_mass);
	setResitution(init_resitution);
	setStaticFriction(init_static_fric);
	setDynamicFriction(init_dynamic_fric);
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
					// Collision - impulse resolution
					glm::vec3 relative_velocity = other->getVelocity() - getVelocity();

					// Get the resitution for this collision
					float collision_resitution = fminf(getRestitution(), other->getRestitution());

					float velocity_along_normal = glm::dot(relative_velocity, collision.getCollisionNormal());

					// Calculate impulse
					float collision_impulse = -(1 + collision_resitution) * velocity_along_normal / (getInvMass() + other->getInvMass());

					// Modify velocity
					setVelocity(getVelocity() - collision_impulse * getInvMass() * collision.getCollisionNormal());
					other->setVelocity(other->getVelocity() + collision_impulse * other->getInvMass() * collision.getCollisionNormal());

					// Friction - friction resolution
					glm::vec3 tangent = glm::normalize(relative_velocity - glm::dot(relative_velocity, collision.getCollisionNormal()) * collision.getCollisionNormal());

					// Calculate friction impulse
					float tangent_impulse = -glm::dot(relative_velocity, tangent) / (getInvMass() + other->getInvMass());

					// Get static friction for this collision
					float static_friction = sqrtf(getStaticFriction() * getStaticFriction() + other->getStaticFriction() * other->getStaticFriction());
					glm::vec3 friction_impulse;
					
					if (fabs(tangent_impulse) < collision_impulse * static_friction)
					{
						friction_impulse = tangent_impulse * tangent;
					}
					else
					{
						// Tangent impulse larger than static friction - use dynamic friction
						float dynamic_friction = sqrtf(getDynamicFriction() * getDynamicFriction() + other->getDynamicFriction() * other->getDynamicFriction());
						friction_impulse = -dynamic_friction * collision_impulse * tangent;
					}

					// Modify velocity
					setVelocity(getVelocity() - getInvMass() * friction_impulse);
					other->setVelocity(other->getVelocity() - other->getInvMass() * friction_impulse);
				}
			}
		}
	}
}