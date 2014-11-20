#pragma once

#include "component.h"
#include "exceptions.h"

#include <glm/glm.hpp>

// Forward Declaration
class RenderingEngine;

class BaseLight : public Component
{
	public:
		BaseLight(glm::vec3& init_color = glm::vec3(), float init_intensity = 1.0f) : color(init_color), intensity(init_intensity) {};
		virtual ~BaseLight() {};
		glm::vec3& getColor() { return color; };
		void setColor(glm::vec3& new_color) { color = new_color; };
		float getIntensity() { return intensity; };
		void setIntensity(float new_intensity) { intensity = new_intensity; };
		// Engine Specific stuff
		void addToRenderingEngine(RenderingEngine *engine) override;
		virtual Shader* getShader() { throw LightException("Base light does not have a real shader"); };
	private:
		glm::vec3 color;
		float intensity;
};

