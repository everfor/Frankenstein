#include "resource_manager.h"
#include "exceptions.h"
#include "utils.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

void ResourceManager::LoadShader(const std::string& fileName, std::string& shader_string)
{
	shader_string.clear();

	std::ifstream file;
	file.open(fileName.c_str());

	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			shader_string.append(line + "\n");
		}
	}
	else
	{
		throw ResourceException("Unable to load shader: " + fileName);
	}
}

void ResourceManager::LoadMesh(std::string& fileName, Mesh& mesh)
{
	std::vector<std::string> splits;
	int split_length = 0;
	split_length = _split_string(fileName, std::string("."), splits);

	if (splits[split_length - 1] == "obj")
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned short> indices;

		loadMeshObj(fileName, vertices, indices);

		mesh.addVertices(vertices, vertices.size(), indices, indices.size());
	}
	else
	{
		throw ResourceException("Mesh loading for file type " + splits[split_length - 1] + " not implemented yet");
	}
}

void ResourceManager::LoadTexture(const std::string& fileName, GLenum textureType)
{
	int width, height, num;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &num, 4);

	if (imageData == NULL)
	{
		throw ResourceException("Failed to load texture file: " + fileName);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

// Private static methods 
void ResourceManager::loadMeshObj(std::string& fileName, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

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
				vertices.push_back(Vertex(glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()), atof(tokens[3].c_str()))));
			}
			else if (tokens[0] == "f")
			{
				// Basic triangulation
				int total_num_indices = tokens.size() - 1;
				int index = 1;

				// Store vertex index
				std::vector<int> vert_indices;
				vert_indices.reserve(total_num_indices);
				for (int i = 1; i <= total_num_indices; i++)
				{
					vert_indices.push_back(atoi(tokens[i].substr(0, tokens[i].find("/")).c_str()) - 1);
					tokens[i].erase(0, tokens[i].find("/") + 1);
				}

				while (index < total_num_indices)
				{
					indices.push_back(vert_indices[(index - 1) % total_num_indices]);
					indices.push_back(vert_indices[index % total_num_indices]);
					indices.push_back(vert_indices[(index + 1) % total_num_indices]);

					index += 2;
				}
			}
		}
	}
	else
	{
		throw ResourceException("Unable to load .obj file: " + fileName);
	}
}
