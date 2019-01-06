#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float aspectRatio, float near, float far)
	:_position(position),
	_target(target),
	_up(up)
{
	_projection = glm::perspective(glm::radians(45.0f), aspectRatio, near, far);
	Update();
}

void Camera::Update()
{	
	_view = glm::lookAt(_position, _target, _up);
}
