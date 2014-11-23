#pragma once

#include "indexed_model.h"
#include "vertex.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Vertex;

class ObjIndex
{
	public:
		ObjIndex(int init_pos_index = 0, int init_tex_index = 0, int init_normal_index = 0) :
			positionIndex(init_pos_index), texIndex(init_tex_index), normalIndex(init_normal_index)
		{};
		int positionIndex;
		int texIndex;
		int normalIndex;
};

class ObjModel : public IndexedModel
{
	public:
		ObjModel(const std::string& fileName);
		virtual ~ObjModel();
		void loadToMesh(Mesh *mesh) override;
	private:
		bool hasTextureCoord;
		bool hasNormalCoord;
		std::vector<Vertex> vertices;
		std::vector<unsigned short> indices;
};

