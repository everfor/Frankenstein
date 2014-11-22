#pragma once

#include "indexed_model.h"

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
		std::vector<glm::vec3>& getPositions() { return positions; };
		std::vector<glm::vec2>& gettexCoords() { return texCoords; };
		std::vector<glm::vec2>& getNormalCoords() { return normalCoords; };
		void loadToMesh(Mesh *mesh) override;
	private:
		static void _calculate_normals(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index);
		bool hasTextureCoord;
		bool hasNormalCoord;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec2> normalCoords;
		std::vector<ObjIndex> indices;
};

