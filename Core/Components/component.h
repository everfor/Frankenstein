#pragma once

#include "transform.h"
#include <cstdarg>

// Forward Declaration
class CoreEngine;
class RenderingEngine;
class Object;
class Shader;
class Transform;

class Component
{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void input(Transform *transform, float delta) {};
		virtual void update(Transform *transform, float delta) {};
		virtual void render(Shader *shader, RenderingEngine *redering_engine) {};
		virtual void setTransform(Transform* new_trans) { transform = new_trans; };
		Transform* getTransform() { return transform; };
		void setEngine(CoreEngine *engine) { addToEngine(engine); };
		virtual void addToEngine(CoreEngine *engine) {};
		virtual void acceptParentObj(Object *obj) {};
	protected:
		CoreEngine *engine;
	private:
		Transform *transform;
};

