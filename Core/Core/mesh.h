#pragma once

#include <GL/glew.h>
#include "vertex.h"

class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();
		void addVertices(Vertex *vertices, int num_vert);
		void draw();
	private:
		GLuint vbo;
		GLuint size;
};

