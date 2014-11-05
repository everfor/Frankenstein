#include "shader.h"
#include "exceptions.h"

Shader::Shader()
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

void Shader::addProgram(std::string& text, GLenum type)
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

void Shader::addFragmentShader(std::string& text)
{
	addProgram(text, GL_FRAGMENT_SHADER);
}

void Shader::addVertexShader(std::string& text)
{
	addProgram(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(std::string& text)
{
	addProgram(text, GL_GEOMETRY_SHADER);
}

void Shader::compileAllShaders()
{
	glLinkProgram(program);

	checkShaderError(program, GL_LINK_STATUS, true, "Program Link Error: ");

	glValidateProgram(program);

	checkShaderError(program, GL_VALIDATE_STATUS, true, "Program Validate Error: ");
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
