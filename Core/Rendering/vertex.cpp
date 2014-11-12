#include "vertex.h"


Vertex::Vertex(const glm::vec3& init_pos, const glm::vec2& init_tex, const glm::vec3& init_normal) :
			pos(init_pos), texCoord(init_tex), normal(init_normal)
{
}

Vertex::~Vertex()
{
}