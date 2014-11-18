#pragma once

#include <GL/glew.h>

class MeshResource
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
		int getRefCount() { return referenceCount; };
		void increaseRefCout() { ++referenceCount; };
		void decreaseRefCout() { --referenceCount; };
		bool hasNoReference() { return referenceCount <= 0; };
	private:
		GLuint vao;						// Vertex Array Object
		GLuint vbo[NUM_BUFFERS];		// Vertex Buffers
		GLuint size;
		int referenceCount;
};
