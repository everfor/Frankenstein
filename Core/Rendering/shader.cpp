#include "shader.h"
#include "exceptions.h"
#include "utils.h"
#include "resource_manager.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

std::map<std::string, std::multimap<std::string, std::string>> Shader::_uniform_structs;

Shader::Shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	program = glCreateProgram();

	if (program == 0)
	{
		throw ShaderException("Shader creation failed. Could not find valid memory location in constructor");
	}

	shaderCount = 0;

	std::string vertex_text, fragment_text;
	ResourceManager::LoadShader(vertex_shader, vertex_text);
	ResourceManager::LoadShader(fragment_shader, fragment_text);

	addVertexShader(vertex_text);
	addFragmentShader(fragment_text);
	compileAllShaders();

	_add_uniform_structs(vertex_text);
	_add_uniform_structs(fragment_text);

	addAllUniforms(vertex_text);
	addAllUniforms(fragment_text);
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

void Shader::addAllUniforms(const std::string& text)
{
	int start = 0;
	while ((start = text.find(UNIFORM_KEYWORD, start)) != std::string::npos)
	{
		int end = text.find(SEMICOLON_KEYWORD, start);
		
		// Get uniform declaration
		std::string uniform = text.substr(start, end - start);
		int first_space = uniform.find(SPACE_KEYWORD);
		int second_space = uniform.find(SPACE_KEYWORD, first_space + 1);

		addUniformWithType(uniform.substr(first_space + 1, second_space - first_space - 1), uniform.substr(second_space + 1));

		start = end;
	}
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

void Shader::updateUniforms(Transform *transform, Camera *camera, Material *material)
{

}

void Shader::addUniformWithType(const std::string& type, const std::string& name)
{
	if (type != SAMPLER_TYPE)
	{
		if (type.find(VEC_TYPE) != std::string::npos || type.find(MAT_TYPE) != std::string::npos
			|| type == FLOAT_TYPE || type == INT_TYPE)
		{
			addUniform(name);
		}
		else
		{
			// Not a basic type - must be a user defined one
			if (_uniform_structs.find(type) == _uniform_structs.end())
			{
				throw ShaderException("Cannot find uniform of type: " + type);
			}

			// Add members as uniforms
			for (std::multimap<std::string, std::string>::iterator it = _uniform_structs.at(type).begin();
				it != _uniform_structs.at(type).end();
				it++)
			{
				addUniformWithType(it->first, name + "." + it->second);
			}
		}
	}
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

void Shader::_add_uniform_structs(const std::string& text)
{
	int start = 0;
	while ((start = text.find(STRUCT_KEYWORD, start)) != std::string::npos)
	{
		int end = text.find(RIGHT_BRACKET_KEYWORD, start);

		std::string struct_string = text.substr(start, end - start + 1);
		// Remove newline characters
		struct_string.erase(std::remove(struct_string.begin(), struct_string.end(), '\n'), struct_string.end());
		struct_string.erase(std::remove(struct_string.begin(), struct_string.end(), '\t'), struct_string.end());
		int left_bracket = struct_string.find(LEFT_BRACKET_KEYWORD);
		int right_bracket = struct_string.find(RIGHT_BRACKET_KEYWORD);

		// Get uniform name
		std::string uniform_name = struct_string.substr(strlen(STRUCT_KEYWORD) + 1, left_bracket - (strlen(STRUCT_KEYWORD) + 1));
		if (_uniform_structs.find(uniform_name) == _uniform_structs.end())
		{
			// New uniform
			_uniform_structs.insert(std::pair<std::string, std::multimap<std::string, std::string>>(uniform_name, std::multimap<std::string, std::string>()));
			
			// Get members
			std::string struct_content = struct_string.substr(left_bracket + 1, right_bracket - (left_bracket + 1));
			std::vector<std::string> members;
			_split_string(struct_content, SEMICOLON_KEYWORD, members);

			for (int i = 0; i < members.size(); i++)
			{
				int space = members[i].find(SPACE_KEYWORD);
				_uniform_structs.at(uniform_name).insert(std::pair<std::string, std::string>(members[i].substr(0, space), members[i].substr(space + 1, members[i].length() - space - 1)));
			}
		}

		start = end;
	}
}