#pragma once

/*
* Just a bunch of uitility functions
*/

#include <vector>
#include <string>
#include <glm/glm.hpp>

// Split string with a delimieter, returns the length of split strings
// No error checking so use with caution
int _split_string(std::string original, const std::string& delimiter, std::vector<std::string>& split_strings);

// Return max component of glm::vec3
float _max_component(glm::vec3& vec);

// Get path of the file
void _get_path(const std::string& fileName, std::string& path);

// Round and normalize to 2 decimal points
void _round_normalize(glm::vec3& vec);

class Collider;
// Return the moment of inertia
float _calculate_moment_of_interia(float mass, Collider* collider);

// Detect if the current machine is storing numbers in big endians or small endians
bool _is_big_endian();

// Convert a character array into corresponding integer
int _char_to_int(const char *buffer, int len);