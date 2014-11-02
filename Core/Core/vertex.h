#pragma once

#include <glm/glm.hpp>

#define VERTEX_SIZE			3

class Vertex
{
	public:
		Vertex(glm::vec3& init_pos);
		virtual ~Vertex();
		void setPose(glm::vec3& new_pos);
		glm::vec3& getPose();
	private:
		glm::vec3 pos;
};

