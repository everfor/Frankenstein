#pragma once

#include <glm/glm.hpp>

#define VERTEX_SIZE			5

class Vertex
{
	public:
		Vertex(const glm::vec3& init_pos, const glm::vec2& init_tex = glm::vec2(0, 0));
		virtual ~Vertex();
		void setPose(const glm::vec3& new_pos) { pos = new_pos; };
		glm::vec3& getPose() { return pos; };
		void setTex(const glm::vec2& new_tex) { texCoord = new_tex; };
		glm::vec2& getTex() { return texCoord; };
	private:
		glm::vec3 pos;
		glm::vec2 texCoord;
};

