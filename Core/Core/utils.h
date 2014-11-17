#pragma once

/*
* Just a bunch of uitility functions
*/

#include "vertex.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>

// Split string with a delimieter, returns the length of split strings
// No error checking so use with caution
int _split_string(std::string original, std::string& delimiter, std::vector<std::string>& split_strings);

// Return max component of glm::vec3
float _max_component(glm::vec3& vec);