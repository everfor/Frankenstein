#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Z is positive pointing out of the screen!!!

class Camera
{
	public:
		Camera(float init_fov, float init_asp, float init_znear, float init_zfar, glm::vec3& init_pos = glm::vec3(0, 0, 2), glm::quat& init_orient = glm::quat(1, 0, 0, 0));
		virtual ~Camera();
		// Position
		glm::vec3& getPos() { return position; };
		void setPos(glm::vec3& new_pos) { position = new_pos; };
		void move(const glm::vec3& dir, float amt);
		void moveX(float amt);
		void moveY(float amt);
		void moveZ(float amt);
		// Orientation
		glm::quat& getOrient() { return orientation; };
		void setOrient(glm::quat& new_orient) { orientation = new_orient; };
		// Angle in degrees
		void rotate(const glm::vec3& axis, float angle);
		void rotateX(float angle);
		void rotateY(float angle);
		void rotateZ(float angle);
		// Other things
		float getFov() { return fov; };
		void setFov(float new_fov) { fov = new_fov; };
		float getAsp() { return aspect; };
		void setAsp(float new_asp) { aspect = new_asp; };
		float getZNear() { return zNear; };
		void setZNear(float new_znear) { zNear = new_znear; };
		float getZFar() { return zFar; };
		void setZFar(float new_zfar) { zFar = new_zfar; };
		// Projection
		glm::mat4& getCameraProjection();
	private:
		glm::vec3 position;
		glm::quat orientation;
		float fov;
		float aspect;
		float zNear;
		float zFar;
		glm::mat4 projection;
};

