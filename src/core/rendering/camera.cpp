#include "camera.h"

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

void Camera::set_position(glm::vec2 position) { _transform.set_position(position); recalculate_matrix(); }
void Camera::set_rotation(float rotation) { _transform.set_rotation(rotation); recalculate_matrix(); }
void Camera::set_scale(glm::vec2 scale) { _transform.set_scale(scale); recalculate_matrix(); }