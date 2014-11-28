#pragma once

#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class CoreEngine;

class Camera : public Component
{
	public:
		Camera(float init_fov, float init_asp, float init_znear, float init_zfar, float init_move_sensitivity = 1.5f, float init_rotate_sensitivity = 7.0f);
		virtual ~Camera();
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
		void setCameraProjection(const glm::mat4& new_projection) { projection = new_projection; transform_locked = true; };
		glm::mat4& getCameraProjection();
		// Override
		void addToEngine(CoreEngine *engine) override;
	private:
		float fov;
		float aspect;
		float zNear;
		float zFar;
		float move_sensitivity;
		float rotate_sensitivity;
		glm::mat4 projection;
		bool transform_locked;
};

