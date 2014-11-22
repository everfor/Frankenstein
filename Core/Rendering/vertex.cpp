#include "vertex.h"


Vertex::Vertex(const glm::vec3& init_pos, const glm::vec2& init_tex, const glm::vec2 init_normal_coord,
	const glm::vec3& init_normal, const glm::vec3& init_tangent, const glm::vec3& init_bitangent) :
			pos(init_pos), texCoord(init_tex), normalCoord(init_normal_coord), normal(init_normal), tangent(init_tangent), bitangent(init_bitangent)
{
}

Vertex::~Vertex()
{
}