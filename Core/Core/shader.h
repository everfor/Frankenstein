#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

class Shader
{
	public:
		Shader();
		virtual ~Shader();
		// Shaders
		void addVertexShader(const std::string& text);
		void addFragmentShader(const std::string& text);
		void addGeometryShader(const std::string& text);
		void compileAllShaders();
		// Uniforms
		void addUniform(const std::string& uniform);
		void setUniformi(const std::string& uniform, const GLint value);
		void setUniformf(const std::string& uniform, const GLfloat value);
		void setUniform(const std::string& uniform, const glm::vec3& value);
		void setUniform(const std::string& uniform, const glm::mat4& value);
		void bind();
	private:
		void addProgram(const std::string& text, GLenum type);
		void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error);
		std::map<std::string, GLuint> uniforms;
		GLuint program;
		unsigned int shaderCount;
		GLuint shaders[3];			// Only have 3 kinds of shaders in total
};