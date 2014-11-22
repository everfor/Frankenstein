#include "obj_model.h"
#include "mesh.h"
#include "utils.h"
#include "exceptions.h"
#include "vertex.h"

#include <fstream>
#include <algorithm>

ObjModel::ObjModel(const std::string& fileName) :
		hasTextureCoord(true), hasNormalCoord(true)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string line;

	// textures
	std::vector<glm::vec2> uvs;

	if (file.is_open())
	{
		std::vector<std::string> tokens;
		while (file.good())
		{
			tokens.clear();
			// Get a new line
			std::getline(file, line);
			_split_string(line, std::string(" "), tokens);
			// Remove empty string
			tokens.erase(
				std::remove_if(tokens.begin(),
				tokens.end(),
				[](const std::string& s) { return s.length() == 0; }),
				tokens.end());

			if (tokens.size() == 0 || tokens[0] == "#")
			{
				continue;
			}
			else if (tokens[0] == "v")
			{
				// Vertex position
				positions.push_back(glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str())));
			}
			else if (tokens[0] == "vt")
			{
				// Vertex texture
				texCoords.push_back(glm::vec2(atof(tokens[1].c_str()), atof(tokens[2].c_str())));
			}
			else if (tokens[0] == "vn")
			{
				// Vertex normal
				normalCoords.push_back(glm::vec2(atof(tokens[1].c_str()), atof(tokens[2].c_str())));
			}
			else if (tokens[0] == "f")
			{
				// Faces - Vertex index
				ObjIndex index[4] = { ObjIndex(), ObjIndex(), ObjIndex(), ObjIndex() };
				for (int i = 1; i <= 3; i++)
				{
					std::vector<std::string> vtns;
					_split_string(tokens[i], std::string("/"), vtns);

					// See if there are textures or normals
					if (hasNormalCoord && vtns.size() < 3)
					{
						hasNormalCoord = false;
					}
					if (hasTextureCoord)
					{
						if (vtns.size() < 2)
						{
							hasTextureCoord = false;
						}
						else if (vtns[1].length() == 0)
						{
							hasTextureCoord = false;
						}
					}

					// Parse
					index[i - 1].positionIndex = atof(vtns[0].c_str()) - 1;
					if (hasTextureCoord)
					{
						index[i - 1].texIndex = atof(vtns[1].c_str()) - 1;
					}
					if (hasNormalCoord)
					{
						index[i - 1].normalIndex = atof(vtns[2].c_str()) - 1;
					}

					indices.push_back(index[i - 1]);
				}

				// Basic triangulation
				if (tokens.size() > 4)
				{
					std::vector<std::string> vtns;
					_split_string(tokens[4], std::string("/"), vtns);

					// See if there are textures or normals
					if (hasNormalCoord && vtns.size() < 3)
					{
						hasNormalCoord = false;
					}
					if (hasTextureCoord)
					{
						if (vtns.size() < 2)
						{
							hasTextureCoord = false;
						}
						else if (vtns[1].length() == 0)
						{
							hasTextureCoord = false;
						}
					}

					// Parse
					index[3].positionIndex = atof(vtns[0].c_str()) - 1;
					if (hasTextureCoord)
					{
						index[3].texIndex = atof(vtns[1].c_str()) - 1;
					}
					if (hasNormalCoord)
					{
						index[3].normalIndex = atof(vtns[2].c_str()) - 1;
					}

					indices.push_back(index[0]);
					indices.push_back(index[2]);
					indices.push_back(index[3]);
				}
			}
		}
	}
	else
	{
		throw ResourceException("Unable to load .obj file: " + fileName);
	}
}

ObjModel::~ObjModel()
{
}

void ObjModel::loadToMesh(Mesh *mesh)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned short> vert_indices;

	// Add positions
	for (int i = 0; i < positions.size(); i++)
	{
		vertices.push_back(Vertex(positions[i]));
	}

	for (int i = 0; i < indices.size(); i++)
	{
		vert_indices.push_back(indices[i].positionIndex);

		if (hasTextureCoord)
		{
			vertices[indices[i].positionIndex].setTex(texCoords[indices[i].texIndex]);
			// If object does not have normal coords, use texture coords instead
			vertices[indices[i].positionIndex].setNormalCoord(texCoords[indices[i].texIndex]);
		}

		if (hasNormalCoord)
		{
			// If object has normal coords, override texture coords
			vertices[indices[i].positionIndex].setNormalCoord(normalCoords[indices[i].normalIndex]);
		}
	}

	_calculate_normals(vertices, vertices.size(), vert_indices, vert_indices.size());

	mesh->addVertices(vertices, vertices.size(), vert_indices, vert_indices.size());
}

void ObjModel::_calculate_normals(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index)
{
	for (int i = 0; i < num_index; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 deltaPos1 = vertices[i1].getPose() - vertices[i0].getPose();
		glm::vec3 deltaPos2 = vertices[i2].getPose() - vertices[i0].getPose();

		glm::vec2 deltaUV1 = vertices[i1].getNormalCoord() - vertices[i0].getNormalCoord();
		glm::vec2 deltaUV2 = vertices[i2].getNormalCoord() - vertices[i0].getNormalCoord();

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		glm::vec3 normal = glm::normalize(glm::cross(deltaPos1, deltaPos2));
		vertices[i0].setNormal(normal);
		vertices[i1].setNormal(normal);
		vertices[i2].setNormal(normal);

		glm::vec3 tangent = glm::normalize((deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r);
		vertices[i0].setTanget(tangent);
		vertices[i1].setTanget(tangent);
		vertices[i2].setTanget(tangent);

		glm::vec3 bitangent = glm::normalize(glm::cross(normal, tangent));
		vertices[i0].setBiTangent(bitangent);
		vertices[i1].setBiTangent(bitangent);
		vertices[i2].setBiTangent(bitangent);
	}
}