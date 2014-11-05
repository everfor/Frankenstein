#include "mesh.h"

Mesh::Mesh() :
		size(0)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
}

void Mesh::addVertices(Vertex *vertices, int num_vert)
{
	glGenBuffers(NUM_BUFFERS, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_vert * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	size = num_vert;
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
}