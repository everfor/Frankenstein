#include "object.h"

Object::Object() :
		transform(Transform())
{
}

Object::~Object()
{
}

void Object::addChild(Object *child)
{
	children.push_back(std::unique_ptr<Object>(child));
}

void Object::addComponent(Component *component)
{
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
	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->update(transform, delta);
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->update(delta);
	}
}

void Object::render(Shader *shader, Camera *camera)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i].get()->render(shader, &transform, camera);
	}

	for (int i = 0; i < children.size(); i++)
	{
		children[i].get()->render(shader, camera);
	}
}