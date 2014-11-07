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
		glm::mat4& getTransformation();
	private:
		glm::vec3 translation;
		glm::mat4 transformation;		// Need to store a final transformation somewhere
};

