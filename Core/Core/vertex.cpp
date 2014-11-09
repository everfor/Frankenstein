#include "vertex.h"


Vertex::Vertex(const glm::vec3& init_pos, const glm::vec2& init_tex) :
			pos(init_pos), texCoord(init_tex)
{
}

Vertex::~Vertex()
{
}