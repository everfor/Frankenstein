#pragma once

#include "mesh.h"
#include "vertex.h"

#include <string>
#include <exception>
#include <vector>
/*
* This class is supposed to serve as a general resource manager (loading files etc.)
*/
class ResourceManager
{
	public:
		// Returns the file content of a shader
		static std::string LoadShader(const std::string& fileName);
		// Parse a mesh file and store the corresponding data in Mesh object
		static void loadMesh(std::string& fileName, Mesh& mesh);
	private:
		ResourceManager();
		// Mesh parsing specifically for ".obj" files
		static void loadMeshObj(std::string& string, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices);
};