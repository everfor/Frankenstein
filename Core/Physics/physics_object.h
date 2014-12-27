#pragma once

#include "component.h"
#include "collider.h"

#include <memory>

class CoreEngine;

class PhysicsObject : public Component
{
	public:
		PhysicsObject(Collider* init_collider = NULL) : collider(std::unique_ptr<Collider>(init_collider))
		{
			if (collider.get() != NULL)
			{
				collider.get()->setTransform(getTransform());
			}
		};
		virtual ~PhysicsObject() {};
		void setCollider(Collider* new_collider)
		{ 
			collider.reset(new_collider); 

			if (new_collider != NULL)
			{
				collider.get()->setTransform(getTransform());
			}
		};
		Collider* getCollider() { return collider.get(); };
		// Used for update in physics engine
		virtual void simulate(float delta) {};
		virtual void addToEngine(CoreEngine* engine);
	private:
		std::unique_ptr<Collider> collider;
};

