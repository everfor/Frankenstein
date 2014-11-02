#pragma once

#include <string>
#include <exception>
/*
* This class is supposed to serve as a general resource manager (loading files etc.)
*/
class ResourceManager
{
	public:
		static std::string LoadShader(const std::string& fileName);
	private:
		ResourceManager();
};