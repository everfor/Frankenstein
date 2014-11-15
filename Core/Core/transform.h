#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "camera.h"

// Directions
#define X_AXIS				glm::vec3(1, 0, 0)
#define Y_AXIS				glm::vec3(0, 1, 0)
#define Z_AXIS				glm::vec3(0, 0, 1)
#define FORWARD_DIR			glm::vec3(0, 0, -1)
#define BACKWARD_DIR		glm::vec3(0, 0, 1)
#define UP_DIR				glm::vec3(0, 1, 0)
#define DOWN_DIR			glm::vec3(0, -1, 0)
#define RIGHT_DIR			glm::vec3(1, 0, 0)
#define LEFT_DIR			glm::vec3(-1, 0, 0)

class Transform
{
	public:
		Transform();
		virtual ~Transform();
		glm::vec3& getTranslation() { return translation; };
		void setTranslation(const glm::vec3& new_translation) { translation = new_translation; };
		void setTranslation(float x, float y, float z) { translation.x = x; translation.y = y; translation.z = z; };
		glm::quat& getRotation() { return rotation; };
		void setRotation(const glm::quat& new_rotation) { rotation = glm::normalize(new_rotation); };
		glm::vec3& getScale() { return scale; };
		void setScale(const glm::vec3& new_scale) { scale = new_scale; };
		void setScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; };
		glm::mat4& getTransformation();
	private:
		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scale;
		glm::mat4 transformation;		// Need to store a final transformation somewhere
};

