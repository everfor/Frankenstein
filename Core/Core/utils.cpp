#include "utils.h"

#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <cassert>

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

#include "collider.h"
#include "sphere_collider.h"

float _calculate_moment_of_interia(float mass, Collider* collider)
{
	if (collider != NULL)
	{
		Collider::_collider_type type = collider->getType();
		if (mass > 0.0f)
		{
			// Only give moi of sphere right now
			if (type == Collider::_collider_type::COLLIDER_SPHERE)
			{
				return 0.4 * mass * ((SphereCollider*)collider)->getRadius() * ((SphereCollider*)collider)->getRadius();
			}
		}
	}

	return 0.0f;
}

bool _is_big_endian()
{
	int test = 1;
	return !((char*)&test)[0];
}

int _char_to_int(const char *buffer, int len)
{
	assert(len >= 0);
	assert(len < 4);

	int result = 0;

	if (!_is_big_endian())
	{
		for (int i = 0; i < len; i++)
		{
			((char*)&result)[i] = buffer[i];
		}
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			((char*)&result)[3 - i] = buffer[i];
		}
	}

	return result;
}