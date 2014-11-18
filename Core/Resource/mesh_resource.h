#pragma once

#include "resource.h"

#include <GL/glew.h>
#include <memory>
#include <map>

class MeshResource;

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
		virtual ~MeshResource();
		GLuint getVAO() { return vao; };
		GLuint getVBO(enum _vertex_buffer_index index) { return vbo[index]; };
		void setSize(GLuint new_size) { size = new_size; };
		GLuint getSize() { return size; };
		// Factory
		static MeshResource* _get_resource(const std::string& fileName);
		static void _remove_resource(const std::string& fileName);
	private:
		GLuint vao;						// Vertex Array Object
		GLuint vbo[NUM_BUFFERS];		// Vertex Buffers
		GLuint size;
		// Factory
		MeshResource();
		static std::map<std::string, std::unique_ptr<MeshResource>> _resources;
};
