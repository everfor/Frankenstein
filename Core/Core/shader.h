#pragma once

#include <GL/glew.h>
#include <string>

class Shader
{
	public:
		Shader();
		virtual ~Shader();
		void addVertexShader(std::string& text);
		void addFragmentShader(std::string& text);
		void addGeometryShader(std::string& text);
		void compileAllShaders();
		void bind();
	private:
		void addProgram(std::string& text, GLenum type);
		void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error);
		GLuint program;
};