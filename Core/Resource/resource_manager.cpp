#include "resource_manager.h"
#include "exceptions.h"
#include "utils.h"
#include "stb_image.h"
#include "indexed_model.h"
#include "obj_model.h"
#include "audio_model.h"
#include "wav_model.h"
#include "display.h"
#include "texture_resource.h"
#include "audio_resource.h"

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

		delete model;
	}
	else
	{
		throw ResourceException("Mesh loading for file type " + splits[split_length - 1] + " not implemented yet");
	}
}

void ResourceManager::LoadTexture(const std::string& file, TextureResource *resource)
{
	int width, height, num;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &num, 4);

	if (data == NULL)
	{
		// throw ResourceException("Failed to load diffuse texture file: " + file);
		data = 0;
		width = resource->getWidth();
		height = resource->getHeight();
	}

	resource->setWidth(width);
	resource->setHeight(height);

	glBindTexture(resource->getTarget(), resource->getTextureID());
	if (resource->getClamp())
	{
		glTexParameteri(resource->getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(resource->getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(resource->getTarget(), GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(resource->getTarget(), GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
		
	glTexParameterf(resource->getTarget(), GL_TEXTURE_MIN_FILTER, resource->getFilter());
	glTexParameterf(resource->getTarget(), GL_TEXTURE_MAG_FILTER, resource->getFilter());

	glTexImage2D(resource->getTarget(), 0, resource->getInternalFormat(), width, height, 0, resource->getFormat(), GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

void ResourceManager::loadAudio(const std::string& fileName, AudioResource *resource)
{
	std::vector<std::string> splits;
	int split_length = 0;
	split_length = _split_string(fileName, std::string("."), splits);

	AudioModel *model;

	if (splits[split_length - 1] == "wav")
	{
		// Parse
		model = new WavModel(std::string(fileName));
		model->loadToAudio(resource);

		delete model;
	}
	else
	{
		throw ResourceException("Audio loading for file " + fileName + " not implemented yet.");
	}
}
