#pragma once

#include <glm/glm.hpp>

class Transform
{
	public:
		Transform();
		virtual ~Transform();
		glm::vec3& getTranslation();
		void setTranslation(const glm::vec3& new_translation);
		void setTranslation(float x, float y, float z);
		glm::vec3& getRotation();
		void setRotation(const glm::vec3& new_rotation);
		void setRotation(float x, float y, float z);
		glm::vec3& getScale();
		void setScale(const glm::vec3& new_scale);
		void setScale(float x, float y, float z);
		glm::mat4& getTransformation();
	private:
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::mat4 transformation;		// Need to store a final transformation somewhere
};

