#include "vertex.h"


Vertex::Vertex(glm::vec3& init_pos) :
			pos(glm::vec3(init_pos))
{
}

Vertex::~Vertex()
{
}

void Vertex::setPose(glm::vec3& new_pos)
{
	pos = glm::vec3(new_pos);
}

glm::vec3& Vertex::getPose()
{
	return glm::vec3(pos);
}