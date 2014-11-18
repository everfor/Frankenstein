#pragma once

#include "resource.h"

#include <GL/glew.h>

class MeshResource : public Resource
{
	public:
		static enum _vertex_buffer_index
		{
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,
			NUM_BUFFERS
		};
		MeshResource();
		virtual ~MeshResource();
		GLuint getVAO() { return vao; };
		GLuint getVBO(enum _vertex_buffer_index index) { return vbo[index]; };
		void setSize(GLuint new_size) { size = new_size; };
		GLuint getSize() { return size; };
	private:
		GLuint vao;						// Vertex Array Object
		GLuint vbo[NUM_BUFFERS];		// Vertex Buffers
		GLuint size;
};
