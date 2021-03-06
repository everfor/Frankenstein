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
class TextureResource;
class AudioResource;
class ResourceManager
{
	public:
		// Returns the file content of a shader
		static void LoadShader(const std::string& fileName, std::string& shader_string);
		// Parse a mesh file and store the corresponding data in Mesh object
		static void LoadMesh(const std::string& fileName, Mesh& mesh);
		// Parse an image file for texture
		static void LoadTexture(const std::string& file, TextureResource *resource);
		// Parse audio file
		static void loadAudio(const std::string& fileName, AudioResource *resource);
	private:
		ResourceManager();
};