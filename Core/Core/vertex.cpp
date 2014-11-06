#include "vertex.h"


Vertex::Vertex(const glm::vec3& init_pos) :
			pos(init_pos)
{
}

Vertex::~Vertex()
{
}

void Vertex::setPose(const glm::vec3& new_pos)
{
	pos = new_pos;
}

glm::vec3& Vertex::getPose()
{
	return pos;
}