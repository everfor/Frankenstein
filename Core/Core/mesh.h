#pragma once

#include <GL/glew.h>
#include <vector>
#include "vertex.h"

class Mesh
{
	public:
		Mesh();
		virtual ~Mesh();
		void addVertices(Vertex *vertices, int num_vert, unsigned short *indices, int num_index);
		void addVertices(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index);
		void draw();
	private:
		enum
		{
			POSITION_VB,
			TEXCOORD_VB,
			INDEX_VB,
			NUM_BUFFERS
		};
		GLuint vao;					// Vertex Array Object
		GLuint vbo[NUM_BUFFERS];		// Vertex Buffers
		GLuint size;
};

