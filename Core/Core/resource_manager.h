#pragma once

#include "mesh.h"
#include "vertex.h"

#include <GL/glew.h>
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
		static void LoadShader(const std::string& fileName, std::string& shader_string);
		// Parse a mesh file and store the corresponding data in Mesh object
		static void LoadMesh(std::string& fileName, Mesh& mesh);
		// Parse an image file for texture
		static void LoadTexture(const std::string& fileName, GLenum textureType);
	private:
		ResourceManager();
		// Mesh parsing specifically for ".obj" files
		static void loadMeshObj(std::string& string, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices);
};