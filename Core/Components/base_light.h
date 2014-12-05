#pragma once

#include "component.h"
#include "exceptions.h"

#include <glm/glm.hpp>
#include <memory>

// Forward Declaration
class CoreEngine;

class Shadow
{
	public:
		Shadow(glm::mat4 init_projection, float init_min_var = 0.0f, float init_light_bleed = 0.0f, bool should_flip_face = false) : 
			projection(init_projection), min_variance(init_min_var), lightbleed_correction(init_light_bleed), flip_face(should_flip_face) {};
		virtual ~Shadow() {};
		glm::mat4& getProjection() { return projection; };
		float getMinVariance() { return min_variance; };
		float getLightBleedCorrection() { return lightbleed_correction; };
		bool shouldFlip() { return flip_face; };
	private:
		glm::mat4 projection;
		float min_variance;
		float lightbleed_correction;
		bool flip_face;
};

class BaseLight : public Component
{
	public:
		BaseLight(glm::vec3& init_color = glm::vec3(), float init_intensity = 1.0f) : color(init_color), intensity(init_intensity), shadow(NULL) {};
		virtual ~BaseLight() {};
		glm::vec3& getColor() { return color; };
		void setColor(glm::vec3& new_color) { color = new_color; };
		float getIntensity() { return intensity; };
		void setIntensity(float new_intensity) { intensity = new_intensity; };
		// Engine Specific stuff
		void addToEngine(CoreEngine *engine) override;
		virtual Shader* getShader() { throw LightException("Base light does not have a real shader"); };
		Shadow* getShadow() { return shadow; };
	protected:
		void setShadow(Shadow *new_shadow) { if (shadow != NULL) { delete shadow; }; shadow = new_shadow; };
	private:
		glm::vec3 color;
		float intensity;
		// Cannot use unique_ptr as advanced lights are decorators
		Shadow* shadow;
};

