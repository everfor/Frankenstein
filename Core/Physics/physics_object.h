#pragma once

#include "component.h"
#include "collider.h"

#include <memory>
#include <glm/glm.hpp>

class CoreEngine;

/*
* Perfect Physics Object - Infinite mass, perfect elastic collision, perfectly smooth (no friction)
*/
class PhysicsObject : public Component
{
	public:
		static enum _physobj_type
		{
			TYPE_GENERAL,
			TYPE_RIGID_BODY
		};
		PhysicsObject(_physobj_type init_type = _physobj_type::TYPE_GENERAL, Collider* init_collider = NULL);
		virtual ~PhysicsObject() {};
		virtual void setCollider(Collider* new_collider);
		Collider* getCollider() { return collider.get(); };
		_physobj_type getType() { return type; };
		// Used for update in physics engine
		virtual void simulate(float delta);
		virtual void collide(PhysicsObject *other) {};
		virtual void addToEngine(CoreEngine* engine);
		// Getters for some members - they are immutable for general phys objects
		glm::vec3& getVelocity() { return velocity; };
		glm::vec3& getAcceleration() { return acceleration; };
		glm::vec3& getAngularVelocity() { return angular_velocity; };
		glm::vec3& getAngularAcceleration() { return angular_acceleration; };
		float getMass() { return mass; };
		float getInvMass() { return inv_mass; };
		float getMOI() { return moment_of_inertia; };
		float getInvMOI() { return inv_moi; };
		float getRestitution() { return resitution; };
		float getStaticFriction() { return static_friction; };
		float getDynamicFriction() { return dynamic_friction; };
		// Layer
		int getLayer() { return layer; };
		void setLayer(int new_layer) { layer = new_layer; };
		void addLayer(int level) { layer |= 1 << level; };
		void removeLyaer(int level) { layer &= !(1 << level); };
		// Override
		virtual void setTransform(Transform *new_transform) override;
		// Setters
		virtual void setVelocity(glm::vec3& new_vel) { velocity = new_vel; };
		virtual void setAcceleration(glm::vec3& new_acc) { acceleration = new_acc; };
		virtual void setAngularVelocity(glm::vec3& new_ang_vel) { angular_velocity = new_ang_vel; };
		virtual void setAngularAcceleration(glm::vec3& new_ang_acc) { angular_acceleration = new_ang_acc; };
		virtual void setMass(float new_mass) {};
		virtual void setResitution(float new_resitution) {};
		virtual void setStaticFriction(float new_static_fric) {};
		virtual void setDynamicFriction(float new_dynamic_fric) {};
		// Impulse
		virtual void applyImpulse(glm::vec3& impulse, glm::vec3& contact_vector) {};
	protected:
		glm::vec3 velocity;
		glm::vec3 acceleration;
		glm::vec3 angular_velocity;
		glm::vec3 angular_acceleration;
		float mass;
		float inv_mass;
		float moment_of_inertia;
		float inv_moi;
		float resitution;
		float static_friction;
		float dynamic_friction;
	private:
		std::unique_ptr<Collider> collider;
		_physobj_type type;
		// Only phys objs that share same level of layers will collide with eath other
		int layer;
};

