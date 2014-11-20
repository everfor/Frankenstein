#pragma once

#include "material.h"
#include "transform.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>

// GLSL shader uniform types
#define FLOAT_TYPE					"float"
#define INT_TYPE					"int"
#define VEC_TYPE					"vec"
#define MAT_TYPE					"mat"
#define SAMPLER_TYPE				"sampler2D"
#define BASE_LIGHT_TYPE				"BaseLight"
#define DIRECTIONAL_LIGHT_TYPE		"DirectionalLight"
#define ATTENUATION_TYPE			"Attenuation"
#define POINT_LIGHT_TYPE			"PointLight"
#define SPOT_LIGHT_TYPE				"SpotLight"
// Keywords
#define UNIFORM_KEYWORD				"uniform"
#define STRUCT_KEYWORD				"struct"
#define SEMICOLON_KEYWORD			";"
#define LEFT_BRACKET_KEYWORD		"{"
#define RIGHT_BRACKET_KEYWORD		"}"
#define SPACE_KEYWORD				" "

// Forward declaration
class Camera;

class Shader
{
	public:
		virtual ~Shader();
		// Shaders
		void addVertexShader(const std::string& text);
		void addFragmentShader(const std::string& text);
		void addGeometryShader(const std::string& text);
		void compileAllShaders();
		// Uniforms
		void addAllUniforms(const std::string& text);
		void addUniform(const std::string& uniform);
		void setUniformi(const std::string& uniform, const GLint value);
		void setUniformf(const std::string& uniform, const GLfloat value);
		void setUniform(const std::string& uniform, const glm::vec3& value);
		void setUniform(const std::string& uniform, const glm::mat4& value);
		virtual void updateUniforms(Transform *transform, Camera *camera, Material *material);
		void bind();
		// Singleton
		static Shader* GetShader() { return NULL; };
	protected:
		Shader(const std::string& vertex_shader, const std::string& fragment_shader);
	private:
		void addUniformWithType(const std::string& type, const std::string& name);
		void addProgram(const std::string& text, GLenum type);
		void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& error);
		std::map<std::string, GLuint> uniforms;
		GLuint program;
		unsigned int shaderCount;
		GLuint shaders[3];
		// User defined structs in GLSL shader (Format: struct, member(type, name))
		static void _add_uniform_structs(const std::string& text);
		static std::map<std::string, std::multimap<std::string, std::string>> _uniform_structs;
};