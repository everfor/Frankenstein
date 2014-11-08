#include "resource_manager.h"
#include "exceptions.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

std::string ResourceManager::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		throw ResourceException("Unable to load shader: " + fileName);
	}

	return output;
}

void ResourceManager::loadMesh(std::string& fileName, Mesh& mesh)
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
				indices.push_back(atoi(tokens[1].c_str()) - 1);
				indices.push_back(atoi(tokens[2].c_str()) - 1);
				indices.push_back(atoi(tokens[3].c_str()) - 1);
			}
		}
	}
	else
	{
		throw ResourceException("Unable to load .obj file: " + fileName);
	}
}
