#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
		void setTranslation(const glm::vec3& new_translation) { translation = new_translation; isTransformationChanged = true; };
		void setTranslation(float x, float y, float z) { translation.x = x; translation.y = y; translation.z = z; isTransformationChanged = true; };
		glm::quat& getRotation() { return rotation; };
		void setRotation(const glm::quat& new_rotation) { rotation = glm::normalize(new_rotation); isTransformationChanged = true; };
		glm::vec3& getScale() { return scale; };
		void setScale(const glm::vec3& new_scale) { scale = new_scale; isTransformationChanged = true; };
		void setScale(float x, float y, float z) { scale.x = x; scale.y = y; scale.z = z; isTransformationChanged = true; };
		bool isChanged() { return isTransformationChanged; };
		void setParent(Transform *new_parent) { parent = new_parent; };
		glm::mat4& getTransformation();
		glm::vec3& getForward() { forward = glm::normalize(glm::mat3_cast(rotation) * FORWARD_DIR); return forward; };
		glm::vec3& getBackward() { backward = glm::normalize(glm::mat3_cast(rotation) * BACKWARD_DIR); return backward; };
		glm::vec3& getRight() { right = glm::normalize(glm::mat3_cast(rotation) * RIGHT_DIR); return right; };
		glm::vec3& getLeft() { left = glm::normalize(glm::mat3_cast(rotation) * LEFT_DIR); return left; };
		glm::vec3& getUp() { up = glm::normalize(glm::mat3_cast(rotation) * UP_DIR); return up; };
		glm::vec3& getDown() { down = glm::normalize(glm::mat3_cast(rotation) * DOWN_DIR); return down; };
		// Get transformed (a.k.a global) stuff
		glm::vec3& getTransformedTranslation();
		glm::quat& getTransformedRotation();
		glm::vec3& getTransformedScale();
		glm::vec3& getTransformedForward();
		glm::vec3& getTransformedBackward();
		glm::vec3& getTransformedRight();
		glm::vec3& getTransformedLeft();
		glm::vec3& getTransformedUp();
		glm::vec3& getTransformedDown();
		// local Movement and Rotation - Theese are local only
		void move(const glm::vec3& dir, float amt);
		void moveX(float amt);
		void moveY(float amt);
		void moveZ(float amt);
		void rotate(const glm::vec3& axis, float angle);		// Angle in degrees for now
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
	private:
		void updateParentTransform();
		Transform *parent;
		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scale;
		bool isTransformationChanged;
		glm::mat4 parentTransformation;
		glm::mat4 transformation;		// Need to store a final transformation somewhere
		// Transformed transformations
		glm::vec3 transformedTranslation;
		glm::quat transformedRotation;
		glm::vec3 transformedScale;
		// directions
		glm::vec3 forward;
		glm::vec3 backward;
		glm::vec3 right;
		glm::vec3 left;
		glm::vec3 up;
		glm::vec3 down;
		// Transformed directions
		glm::vec3 transformedForward;
		glm::vec3 transformedBackward;
		glm::vec3 transformedRight;
		glm::vec3 transformedLeft;
		glm::vec3 transformedUp;
		glm::vec3 transformedDown;
};

