#pragma once

/*
* Just a bunch of uitility functions
*/

#include "vertex.h"

#include <vector>
#include <string>

// Split string with a delimieter, returns the length of split strings
// No error checking so use with caution
int _split_string(std::string original, std::string& delimiter, std::vector<std::string>& split_strings);

// Calculate normals for vertices
void _calculate_normals(std::vector<Vertex>& vertices, int num_vert, std::vector<unsigned short>& indices, int num_index);