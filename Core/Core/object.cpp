#include "object.h"

#include "core_engine.h"

Object::Object() :
		transform(Transform())
{
}

Object::~Object()
{
}

void Object::setEngine(CoreEngine *new_engine)
{
	if (engine != new_engine)
	{
		engine = new_engine;

		for (int i = 0; i < children.size(); i++)
		{
			children[i].get()->setEngine(engine);
		}

		for (int i = 0; i < components.size(); i++)
		{
			components[i].get()->setEngine(engine);
		}
	}
}

void Object::addChild(Object *child)
{
	if (engine != NULL)
	{
		child->setEngine(engine);
	}
	child->getTransform().setParent(&transform);
	children.push_back(std::unique_ptr<Object>(child));
}

void Object::addComponent(Component *component)
{
	if (engine != NULL)
	{
		component->setEngine(engine);
	}
	// Components are supposed to be in the same position as the object that holds them
	component->setTransform(&transform);
	components.push_back(std::unique_ptr<Component>(component));
}

void Object::input(float delta)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->input(&transform, delta);
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->input(delta);
	}
}

void Object::update(float delta)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->update(delta);
	}

	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->update(&transform ,delta);
	}
}

void Object::render(Shader *shader, RenderingEngine *rendering_engine)
{
	// Somehow children needs to be rendered first
	// In order to avoid weird texture overlapping issues
	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->render(shader, rendering_engine);
	}

	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->render(shader, rendering_engine);
	}
}