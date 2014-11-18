#include "object.h"

#include "rendering_engine.h"

Object::Object() :
		transform(Transform())
{
}

Object::~Object()
{
}

void Object::addChild(Object *child)
{
	child->getTransform().setParent(&transform);
	children.push_back(std::unique_ptr<Object>(child));
}

void Object::addComponent(Component *component)
{
	// Components are supposed to be in the same position as the object that holds them
	component->setTransform(&transform);
	components.push_back(std::unique_ptr<Component>(component));
}

void Object::input(float delta)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->input(transform, delta);
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
		components[i].get()->update(transform, delta);
	}
}

void Object::render(Shader *shader, Camera *camera)
{
	// Somehow children needs to be rendered first
	// In order to avoid weird texture overlapping issues
	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->render(shader, camera);
	}

	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->render(shader, camera);
	}
}

void Object::addToRenderingEngine(RenderingEngine *engine)
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->addToRenderingEngine(engine);
	}

	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->addToRenderingEngine(engine);
	}
}