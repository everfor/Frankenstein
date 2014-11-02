#include "mesh.h"

Mesh::Mesh() :
		size(0)
{
	glGenBuffers(1, &vbo);
}


Mesh::~Mesh()
{
}

void Mesh::addVertices(Vertex *vertices, int num_vert)
{
	size = num_vert;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
}

void Mesh::draw()
{
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float), 0);
	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
}