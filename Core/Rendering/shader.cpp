#include "shader.h"
#include "exceptions.h"
#include "utils.h"
#include "resource_manager.h"
#include "camera.h"
#include "material.h"
#include "rendering_engine.h"
//	Lightings
#include "base_light.h"
#include "directional_light.h"
#include "point_light.h"
#include "spot_light.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

std::map<std::string, std::multimap<std::string, std::string>> Shader::_uniform_structs;
std::map<Shader::_shader_type, std::unique_ptr<Shader>> Shader::_shaders;

Shader::Shader(_shader_type shader_type, const std::string& vertex_shader, const std::string& fragment_shader) : type(shader_type)
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

void Shader::addUniform(const std::string& uniform, const std::string& type)
{
	GLuint uniform_loc = glGetUniformLocation(program, uniform.c_str());

	if (uniform_loc == 0xFFFFFFFF)
	{
		throw ShaderException("Could not find uniform" + uniform);
	}

	uniforms.insert(std::pair<std::string, std::pair<std::string, GLuint>>(uniform, std::pair<std::string, GLuint>(type, uniform_loc)));
}

void Shader::setUniformi(const std::string& uniform, const GLint value)
{
	glUniform1i(uniforms.at(uniform).second, value);
}

void Shader::setUniformf(const std::string& uniform, const GLfloat value)
{
	glUniform1f(uniforms.at(uniform).second, value);
}

void Shader::setUniform(const std::string& uniform, const glm::vec3& value)
{
	glUniform3f(uniforms.at(uniform).second, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(uniforms.at(uniform).second, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& uniform, BaseLight& base)
{
	setUniform(uniform + ".color", base.getColor());
	setUniformf(uniform + ".intensity", base.getIntensity());
}

void Shader::setUniform(const std::string& uniform, DirectionalLight& directionalLight)
{
	setUniform(uniform + ".base", (BaseLight)directionalLight);
	setUniform(uniform + ".direction", directionalLight.getDirection());
}

void Shader::setUniform(const std::string& uniform, PointLight& pointLight)
{
	setUniform(uniform + ".base", (BaseLight)pointLight);
	setUniform(uniform + ".position", pointLight.getTransform()->getTransformedTranslation());
	setUniformf(uniform + ".atten.constant", pointLight.getConstant());
	setUniformf(uniform + ".atten.linear", pointLight.getLinear());
	setUniformf(uniform + ".atten.exponent", pointLight.getExponent());
	setUniformf(uniform + ".range", pointLight.getRange());
}

void Shader::setUniform(const std::string& uniform, SpotLight& spotLight)
{
	setUniform(uniform + ".pointLight", (PointLight)spotLight);
	setUniform(uniform + ".direction", spotLight.getDirection());
	setUniformf(uniform + ".cutoff", spotLight.getCutOff());
}

void Shader::updateUniforms(Transform *transform, RenderingEngine *rendering_engine, Material *material)
{
	for (std::map<std::string, std::pair<std::string, GLuint>>::iterator it = uniforms.begin();
		it != uniforms.end();
		it++)
	{
		if (it->first == UNIFORM_MODEL)
		{
			setUniform(it->first, transform->getTransformation());
		}
		else if (it->first == UNIFORM_MVP)
		{
			setUniform(it->first, rendering_engine->getMainCamera()->getCameraProjection() * transform->getTransformation());
		}
		else if (it->first == UNIFORM_EYE_POS)
		{
			setUniform(it->first, rendering_engine->getMainCamera()->getTransform()->getTranslation());
		}
		else if (it->first == UNIFORM_SPEC_INTENSITY)
		{
			setUniformf(it->first, material->getFloat(MATERIAL_SPECULAR_INTENSITY));
		}
		else if (it->first == UNIFORM_SPEC_EXP)
		{
			setUniformf(it->first, material->getFloat(MATERIAL_SPECULAR_EXPONENT));
		}
		else if (it->first == UNIFORM_DISP_BIAS)
		{
			setUniformf(it->first, material->getFloat(MATERIAL_DISP_BIAS));
		}
		else if (it->first == UNIFORM_DISP_BIAS)
		{
			setUniformf(it->first, material->getFloat(MATERIAL_DISP_SCALE));
		}
		else if (it->first == UNIFORM_DIFFUSE_SAMPLER)
		{
			setUniformi(it->first, DIFFUSE_TEXTEURE_SLOT);
			material->getTexture(MATERIAL_DIFFUSE_TEXTURE).bind(DIFFUSE_TEXTEURE_SLOT);
		}
		else if (it->first == UNIFORM_NORMAL_SAMPLER)
		{
			setUniformi(it->first, NORMAL_TEXTURE_SLOT);
			material->getTexture(MATERIAL_NORMAL_TEXTURE).bind(NORMAL_TEXTURE_SLOT);
		}
		else if (it->first == UNIFORM_DISP_SAMPLER)
		{
			setUniformi(it->first, DISP_TEXTURE_SLOT);
			material->getTexture(MATERIAL_DISP_TEXTURE).bind(DISP_TEXTURE_SLOT);
		}
	}

	// Set Light Uniforms
	switch (type)
	{
		case Shader::AMBIENT_LIGHT:
			setUniform(UNIFORM_AMBIENT_LIGHT, light->getColor());
			break;
		case Shader::DIRECTIONAL_LIGHT:
			setUniform(UNIFORM_DIRECTIONAL_LIGHT, (DirectionalLight)*light);
			break;
		case Shader::POINT_LIGHT:
			setUniform(UNIFORM_POINT_LIGHT, (PointLight)*light);
			break;
		case Shader::SPOT_LIGHT:
			setUniform(UNIFORM_SPOT_LIGHT, (SpotLight)((PointLight)*light));
			break;
		default:
			break;
	}
}

void Shader::addUniformWithType(const std::string& type, const std::string& name)
{
	if (type.find(VEC_TYPE) != std::string::npos || type.find(MAT_TYPE) != std::string::npos
		|| type == FLOAT_TYPE || type == INT_TYPE || type == SAMPLER_TYPE)
	{
		addUniform(name, type);
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

void Shader::bind()
{
	glUseProgram(program);
}

Shader* Shader::GetShader(Shader::_shader_type type, BaseLight* light)
{
	if (_shaders.find(type) == _shaders.end())
	{
		switch (type)
		{
			case _shader_type::AMBIENT_LIGHT:
				_shaders.insert(std::pair<_shader_type, std::unique_ptr<Shader>>(type, 
					std::unique_ptr<Shader>(new Shader(type, "./res/shaders/forward-ambient.vs",
														"./res/shaders/forward-ambient.fs"))));
				break;
			case _shader_type::DIRECTIONAL_LIGHT:
				_shaders.insert(std::pair<_shader_type, std::unique_ptr<Shader>>(type,
					std::unique_ptr<Shader>(new Shader(type, "./res/shaders/forward-directional.vs",
														"./res/shaders/forward-directional.fs"))));
				break;
			case _shader_type::POINT_LIGHT:
				_shaders.insert(std::pair<_shader_type, std::unique_ptr<Shader>>(type,
					std::unique_ptr<Shader>(new Shader(type, "./res/shaders/forward-point.vs",
														"./res/shaders/forward-point.fs"))));
				break;
			case _shader_type::SPOT_LIGHT:
				_shaders.insert(std::pair<_shader_type, std::unique_ptr<Shader>>(type,
					std::unique_ptr<Shader>(new Shader(type, "./res/shaders/forward-spot.vs",
														"./res/shaders/forward-spot.fs"))));
				break;
		}
	}

	_shaders.at(type).get()->setLight(light);

	return _shaders.at(type).get();
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