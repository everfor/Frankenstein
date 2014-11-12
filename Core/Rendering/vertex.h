#pragma once

#include <glm/glm.hpp>

#define VERTEX_SIZE			8

class Vertex
{
	public:
		Vertex(const glm::vec3& init_pos, const glm::vec2& init_tex = glm::vec2(0, 0), const glm::vec3& init_normal = glm::vec3(0, 0, 0));
		virtual ~Vertex();
		void setPose(const glm::vec3& new_pos) { pos = new_pos; };
		glm::vec3& getPose() { return pos; };
		void setTex(const glm::vec2& new_tex) { texCoord = new_tex; };
		glm::vec2& getTex() { return texCoord; };
		glm::vec3& getNormal() { return normal; };
		void setNormal(glm::vec3& new_normal) { normal = new_normal; };
	private:
		glm::vec3 pos;
		glm::vec2 texCoord;
		glm::vec3 normal;
};

