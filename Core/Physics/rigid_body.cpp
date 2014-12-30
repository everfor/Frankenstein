#include "rigid_body.h"
#include "object.h"
#include "transform.h"
#include "utils.h"

RigidBody::RigidBody(glm::vec3& init_vel, glm::vec3& init_acc, glm::vec3& init_ang_vel, glm::vec3& init_ang_acc, float init_mass, float init_resitution, float init_static_fric, float init_dynamic_fric) :
			PhysicsObject(PhysicsObject::_physobj_type::TYPE_RIGID_BODY)
{
	setVelocity(init_vel);
	setAcceleration(init_acc);
	setAngularVelocity(init_ang_vel);
	setAngularAcceleration(init_ang_acc);
	setMass(init_mass);
	setResitution(init_resitution);
	setStaticFriction(init_static_fric);
	setDynamicFriction(init_dynamic_fric);
}

void RigidBody::setCollider(Collider *new_collider)
{
	PhysicsObject::setCollider(new_collider);

	moment_of_inertia = _calculate_moment_of_interia(mass, getCollider());
	if (moment_of_inertia == 0.0f)
	{
		inv_moi = 0.0f;
	}
	else
	{
		inv_moi = 1.0 / moment_of_inertia;
	}
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

	// Moment of intertia
	moment_of_inertia = _calculate_moment_of_interia(mass, getCollider());
	if (moment_of_inertia == 0.0f)
	{
		inv_moi = 0.0f;
	}
	else
	{
		inv_moi = 1.0 / moment_of_inertia;
	}
}

void RigidBody::applyImpulse(glm::vec3& impulse, glm::vec3& contact_vector)
{
	// Apply impulse on linear velocity
	setVelocity(getVelocity() + impulse * getInvMass());

	// Apply impulse on angular velocity
	setAngularVelocity(getAngularVelocity() + glm::cross(contact_vector, impulse) * getInvMOI());
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
					/*
					**************************************************
					*************** Normal Collision******************
					**************************************************
					*/
					glm::vec3 contact_radius_a = collision.getContactRadiusA();
					glm::vec3 contact_radius_b = collision.getContactRadiusB();

					glm::vec3 relative_velocity = other->getVelocity() - getVelocity();

					// Get the resitution for this collision
					float collision_resitution = fminf(getRestitution(), other->getRestitution());

					float velocity_along_normal = glm::dot(relative_velocity, collision.getCollisionNormal());

					// Calculate impulse
					float normal_impulse = -(1 + collision_resitution) * velocity_along_normal / (getInvMass() + other->getInvMass());
					glm::vec3 collision_impulse = normal_impulse * collision.getCollisionNormal();

					// Apply Impulse
					applyImpulse(-collision_impulse, contact_radius_a);
					other->applyImpulse(collision_impulse, contact_radius_b);

					/*
					**************************************************
					*************** Tangent Friction******************
					**************************************************
					*/
					glm::vec3 tangent = glm::normalize(relative_velocity - glm::dot(relative_velocity, collision.getCollisionNormal()) * collision.getCollisionNormal());
					float angular_inertia_a = glm::length(glm::cross(contact_radius_a, tangent));
					float angular_inertia_b = glm::length(glm::cross(contact_radius_b, tangent));

					// Used to calculate friction generated from rotations of the two colliders
					float angular_impulse_a = glm::dot(glm::cross(contact_radius_a, getAngularVelocity()), tangent);
					float angular_impulse_b = glm::dot(glm::cross(contact_radius_b, other->getAngularVelocity()), tangent);

					// Calculate friction impulse
					float tangent_impulse = -(1 + collision_resitution) * glm::dot(relative_velocity, tangent) 
						/ (getInvMass() + other->getInvMass() 
						+ angular_inertia_a * angular_inertia_a * getInvMOI()
						+ angular_inertia_b * angular_inertia_b * getInvMOI())
						+ angular_impulse_a * static_friction
						+ angular_impulse_b * static_friction;

					// Get static friction for this collision
					float static_friction = FRICTION_CONSTANT_CORRECTION * sqrtf(getStaticFriction() * getStaticFriction() + other->getStaticFriction() * other->getStaticFriction());
					glm::vec3 friction_impulse;
					
					if (fabs(tangent_impulse) < normal_impulse * static_friction)
					{
						friction_impulse = (tangent_impulse) * tangent;
					}
					else
					{
						// Tangent impulse larger than static friction - use dynamic friction
						float dynamic_friction = sqrtf(getDynamicFriction() * getDynamicFriction() + other->getDynamicFriction() * other->getDynamicFriction()) / FRICTION_CONSTANT_CORRECTION;
						friction_impulse = (-dynamic_friction * collision_impulse
											+ angular_impulse_a * dynamic_friction
											+ angular_impulse_b * dynamic_friction) * tangent;
					}

					// Apply Impulse
					applyImpulse(-friction_impulse, contact_radius_a);
					other->applyImpulse(friction_impulse, contact_radius_b);
				}
			}
		}
	}
}