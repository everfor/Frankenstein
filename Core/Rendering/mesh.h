#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include <memory>

#include "vertex.h"
#include "mesh_resource.h"

class Mesh
{
	public:
		Mesh(const std::string& fileName = "");
		virtual ~Mesh();
		void addVertices(Vertex *vertices, int num_vert, unsigned short *indices, int num_index);
		void addVertices(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index);
		void draw();
	private:
		std::string fileName;
		MeshResource *resource;
};

