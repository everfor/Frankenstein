#include "physics_object.h"
#include "core_engine.h"
#include "physics_engine.h"

#include <glm/gtx/quaternion.hpp>

PhysicsObject::PhysicsObject(_physobj_type init_type, Collider* init_collider) : 
			velocity(glm::vec3()), acceleration(glm::vec3()), mass(0.0f), inv_mass(0.0f), moment_of_inertia(0.0f), inv_moi(0.0f),
			resitution(1.0f), static_friction(0.0f), dynamic_friction(0.0f),
			collider(std::unique_ptr<Collider>(init_collider)), type(init_type), layer(1),
			impact_sound(std::unique_ptr<Audio>())
{
	if (collider.get() != NULL)
	{
		collider.get()->setTransform(getTransform());
	}
}

void PhysicsObject::addToEngine(CoreEngine* engine)
{
	engine->getPhysicsEngine()->addObject(this);

	this->engine = engine;

	if (impact_sound.get() != NULL)
	{
		impact_sound.get()->setEngine(engine);
	}
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

void PhysicsObject::simulate(float delta)
{
	// Apply gravity
	setVelocity(getVelocity() + getMass() * getInvMass() * engine->getPhysicsEngine()->getGravitationalAcc());
	// Update velocity
	setVelocity(getVelocity() + delta * getAcceleration());
	// Velocity is always local
	getTransform()->setTranslation(getTransform()->getTranslation() + velocity * delta);

	// Update angular velocity
	setAngularVelocity(getAngularVelocity() + delta * getAngularAcceleration());
	// Update orientation
	glm::quat row = glm::angleAxis(angular_velocity.x, X_AXIS);
	glm::quat pitch = glm::angleAxis(angular_velocity.y, Y_AXIS);
	glm::quat yaw = glm::angleAxis(angular_velocity.z, Z_AXIS);

	getTransform()->setRotation(getTransform()->getRotation() * row * pitch * yaw);
}

void PhysicsObject::setImpactSound(Audio* new_sound)
{
	impact_sound.reset(new_sound);

	if (impact_sound.get() != NULL)
	{
		impact_sound.get()->setEngine(engine);
	}
}