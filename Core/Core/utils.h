#pragma once

/*
* Just a bunch of uitility functions
*/

#include <vector>
#include <string>

// Split string with a delimieter, returns the length of split strings
// No error checking so use with caution
int _split_string(std::string original, std::string& delimiter, std::vector<std::string>& split_strings);