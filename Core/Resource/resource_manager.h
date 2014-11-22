#pragma once

#include "mesh.h"
#include "vertex.h"

#include <GL/glew.h>
#include <string>
#include <exception>
#include <vector>

// Shader related macros
#define INCLUDE_KEYWORD			"#include"

/*
* This class is supposed to serve as a general resource manager (loading files etc.)
*/
class ResourceManager
{
	public:
		// Returns the file content of a shader
		static void LoadShader(const std::string& fileName, std::string& shader_string);
		// Parse a mesh file and store the corresponding data in Mesh object
		static void LoadMesh(const std::string& fileName, Mesh& mesh);
		// Parse an image file for texture
		static void LoadTexture(GLuint texture, const std::string& diffuse_texture);
	private:
		ResourceManager();
};