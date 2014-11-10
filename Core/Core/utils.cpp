#include "utils.h"

#include <glm/glm.hpp>

int _split_string(std::string original, std::string& delimiter, std::vector<std::string>& split_strings)
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

void _calculate_normals(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index)
{
	for (int i = 0; i < num_index; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 normal = glm::normalize(glm::cross(vertices[i1].getPose() - vertices[i0].getPose(), vertices[i2].getPose() - vertices[i0].getPose()));
		vertices[i0].setNormal(normal);
		vertices[i1].setNormal(normal);
		vertices[i2].setNormal(normal);
	}
}