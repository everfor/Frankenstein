#include "utils.h"

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