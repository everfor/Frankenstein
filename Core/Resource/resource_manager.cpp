#include "resource_manager.h"
#include "exceptions.h"
#include "utils.h"
#include "stb_image.h"
#include "indexed_model.h"
#include "obj_model.h"

#include <glm/glm.hpp>
#include <fstream>
#include <algorithm>
#include <stdlib.h>

void ResourceManager::LoadShader(const std::string& fileName, std::string& shader_string)
{
	shader_string.clear();

	// Find path of the file - for later use
	std::string path;
	_get_path(fileName, path);

	std::ifstream file;
	file.open(fileName.c_str());

	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			if (line.find(INCLUDE_KEYWORD) != std::string::npos)
			{
				// Parse included files
				std::vector<std::string> include_file;
				_split_string(line, " ", include_file);

				std::string included_file_string;
				LoadShader(path + include_file[1].substr(1, include_file[1].length() - 2), included_file_string);

				shader_string.append(included_file_string + "\n");
			}
			else
			{
				shader_string.append(line + "\n");
			}
		}
	}
	else
	{
		throw ResourceException("Unable to load shader: " + fileName);
	}
}

void ResourceManager::LoadMesh(const std::string& fileName, Mesh& mesh)
{
	std::vector<std::string> splits;
	int split_length = 0;
	split_length = _split_string(fileName, std::string("."), splits);

	IndexedModel *model;

	if (splits[split_length - 1] == "obj")
	{
		model = new ObjModel(fileName);
		model->loadToMesh(&mesh);

		free(model);
	}
	else
	{
		throw ResourceException("Mesh loading for file type " + splits[split_length - 1] + " not implemented yet");
	}
}

void ResourceManager::LoadTexture(const std::string& fileName, GLuint texture)
{
	int width, height, num;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &num, 4);

	if (imageData == NULL)
	{
		throw ResourceException("Failed to load texture file: " + fileName);
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}
