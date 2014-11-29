#include "utils.h"

#include <glm/glm.hpp>
#include <cmath>
#include <iostream>

int _split_string(std::string original, const std::string& delimiter, std::vector<std::string>& split_strings)
{
	size_t pos = 0;
	int count = 0;
	while ((pos = original.find(delimiter)) != std::string::npos)
	{
		count++;
		split_strings.push_back(original.substr(0, pos));
		original.erase(0, pos + delimiter.length());
	}

	if (original.length() > 0)
	{
		count++;
		split_strings.push_back(original);
	}

	return count;
}

float _max_component(glm::vec3& vec)
{
	return std::fmaxf(vec.x, fmaxf(vec.y, vec.z));
}

void _get_path(const std::string& fileName, std::string& path)
{
	int pos = 0, cursor = 0;
	while ((cursor = fileName.find('/', pos + 1)) != std::string::npos)
	{
		pos = cursor;
	}

	path = fileName.substr(0, pos + 1);
}

void _round_normalize(glm::vec3& vec)
{
	//std::cout << "Before Vec: " << vec.x << " " << vec.y << " " << vec.z << std::endl;

	vec.x = (int)(vec.x * 10) / 10.0f;
	vec.y = (int)(vec.y * 10) / 10.0f;
	vec.z = (int)(vec.z * 10) / 10.0f;

	// std::cout << "Vec: " << vec.x << " " << vec.y << " " << vec.z << std::endl;

	vec = glm::normalize(vec);
}