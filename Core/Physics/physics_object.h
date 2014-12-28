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
		void setCollider(Collider* new_collider);
		Collider* getCollider() { return collider.get(); };
		_physobj_type getType() { return type; };
		// Used for update in physics engine
		virtual void simulate(float delta) {};
		virtual void collide(PhysicsObject *other) {};
		virtual void addToEngine(CoreEngine* engine);
		// Getters for some members - they are immutable for general phys objects
		glm::vec3& getVelocity() { return velocity; };
		float getMass() { return mass; };
		float getInvMass() { return inv_mass; };
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
		virtual void setMass(float new_mass) {};
		virtual void setResitution(float new_resitution) {};
		virtual void setStaticFriction(float new_static_fric) {};
		virtual void setDynamicFriction(float new_dynamic_fric) {};
	protected:
		glm::vec3 velocity;
		float mass;
		float inv_mass;
		float resitution;
		float static_friction;
		float dynamic_friction;
	private:
		std::unique_ptr<Collider> collider;
		_physobj_type type;
		// Only phys objs that share same level of layers will collide with eath other
		int layer;
};

