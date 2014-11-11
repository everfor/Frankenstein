#include "shader.h"
#include "exceptions.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

Shader::Shader() :
			uniforms(std::map<std::string, GLuint>())
{
	program = glCreateProgram();

	if (program == 0)
	{
		throw ShaderException("Shader creation failed. Could not find valid memory location in constructor");
	}

	shaderCount = 0;
}

Shader::~Shader()
{
	while (shaderCount > 0)
	{
		glDetachShader(program, shaders[--shaderCount]);
		glDeleteShader(shaders[shaderCount]);
	}

	glDeleteProgram(program);
}

void Shader::addProgram(const std::string& text, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
	{
		throw ShaderException("Shader creation failed. Could not find valid memory location when creating shader");
	}

	const GLchar* shader_text[1];
	GLint shader_text_length[1];
	shader_text[0] = text.c_str();
	shader_text_length[0] = text.length();

	glShaderSource(shader, 1, shader_text, shader_text_length);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader Compile Error: ");

	shaders[shaderCount++] = shader;

	glAttachShader(program, shader);
}

void Shader::addFragmentShader(const std::string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addVertexShader(const std::string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const std::string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

/*
 * DONT FORGET TO CALL DIS METHOD YOU SCRUB
 */
void Shader::compileAllShaders()
{
	glLinkProgram(program);

	checkShaderError(program, GL_LINK_STATUS, true, "Program Link Error: ");

	glValidateProgram(program);

	checkShaderError(program, GL_VALIDATE_STATUS, true, "Program Validate Error: ");
}

void Shader::addUniform(const std::string& uniform)
{
	GLuint uniform_loc = glGetUniformLocation(program, uniform.c_str());

	if (uniform_loc == 0xFFFFFFFF)
	{
		throw ShaderException("Could not find uniform" + uniform);
	}

	uniforms.insert(std::pair<std::string, GLuint>(uniform, uniform_loc));
}

void Shader::setUniformi(const std::string& uniform, const GLint value)
{
	glUniform1i(uniforms.at(uniform), value);
}

void Shader::setUniformf(const std::string& uniform, const GLfloat value)
{
	glUniform1f(uniforms.at(uniform), value);
}

void Shader::setUniform(const std::string& uniform, const glm::vec3& value)
{
	glUniform3f(uniforms.at(uniform), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(uniforms.at(uniform), 1, GL_FALSE, glm::value_ptr(value)); 
}

void Shader::updateUniforms(Transform& transform, Camera& camera, Material& material)
{

}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error)
{
	GLint success = 0;
	GLchar error_msg[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error_msg), NULL, error_msg);
		else
			glGetShaderInfoLog(shader, sizeof(error_msg), NULL, error_msg);

		throw ShaderException(std::string(error + std::string(error_msg))); 
	}
}
