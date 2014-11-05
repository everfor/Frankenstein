#include "resource_manager.h"
#include "exceptions.h"

#include <fstream>

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
