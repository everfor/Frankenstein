#include "mesh_resource.h"

MeshResource::MeshResource() : size(0)
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
