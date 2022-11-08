#include "camera.h"
#include <iostream>

void Camera::recalculate_matrix() {
	_view_projection = _projection * _transform.get_matrix();
}

Camera::Camera() {
	_projection = glm::ortho(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f);
	_transform = Transform();
	recalculate_matrix();
}

Camera::Camera(float left, float right, float top, float bottom, float near, float far) {
	_projection = glm::ortho(left, right, top, bottom, near, far);
	_transform = Transform();
	recalculate_matrix();
}

void Camera::set_bounds(float left, float right, float top, float bottom, float near, float far) {
	_projection = glm::ortho(left, right, top, bottom, near, far);
	recalculate_matrix();
}