#include "mesh_resource.h"
#include "exceptions.h"

std::map<std::string, std::unique_ptr<MeshResource>> MeshResource::_resources;

MeshResource::MeshResource() : Resource(), size(0)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(NUM_BUFFERS, vbo);

	increaseRefCout();
}

MeshResource::~MeshResource()
{
	glDeleteBuffers(NUM_BUFFERS, vbo);
	glDeleteVertexArrays(1, &vao);
}

MeshResource* MeshResource::_get_resource(const std::string& fileName)
{
	if (_resources.find(fileName) != _resources.end())
	{
		_resources.at(fileName).get()->increaseRefCout();
		return _resources.at(fileName).get();
	}

	_resources.insert(std::pair<std::string, std::unique_ptr<MeshResource>>(fileName, std::unique_ptr<MeshResource>(new MeshResource())));
	return _resources.at(fileName).get();
}

void MeshResource::_remove_resource(const std::string& fileName)
{
	if (_resources.find(fileName) == _resources.end())
	{
		throw ResourceException("No mesh resource named " + fileName + " found.");
	}

	_resources.at(fileName).get()->decreaseRefCout();
	if (_resources.at(fileName).get()->hasNoReference())
	{
		_resources.erase(fileName);
	}
}
