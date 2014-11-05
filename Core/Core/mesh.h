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
		enum
		{
			POSITION_VB,
			NUM_BUFFERS
		};
		GLuint vao;					// Vertex Array Object
		GLuint vbo[NUM_BUFFERS];		// Vertex Buffers
		GLuint size;
};

