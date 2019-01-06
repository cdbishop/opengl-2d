#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "System/Windows_defuckery.h"

#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float aspectRatio, float near, float far);

	glm::vec3& GetPosition() {
		return _position;
	}

	glm::vec3& GetTarget() {
		return _target;
	}

	glm::vec3 GetUp() {
		return _up;
	}

	virtual void Update();

	glm::mat4& GetView() {
		return _view;
	}

	glm::mat4& GetProjection() {
		return _projection;
	}

protected:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 _up;

	glm::mat4 _projection;
	glm::mat4 _view;
};