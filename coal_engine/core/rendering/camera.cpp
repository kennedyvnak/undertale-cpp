#include "enpch.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace engine {
	Camera::Camera()
		: _transform(), _near(-1.0f), _far(1.0f), _aspect_ratio(16.0f / 9.0f), _size(5.0f) {
		recalculate_projection();
		recalculate_matrix();
	}

	void Camera::recalculate_matrix() {
		_view_projection = _projection * _transform.get_matrix();
	}

	void Camera::recalculate_projection() {
		_projection = glm::ortho(-_aspect_ratio * _size, _aspect_ratio * _size, -_size, _size, _near, _far);
		recalculate_matrix();
	}

	void Camera::set_position(glm::vec2 position) { _transform.set_position(position); recalculate_matrix(); }
	void Camera::set_rotation(float rotation) { _transform.set_rotation(rotation); recalculate_matrix(); }
	void Camera::set_scale(glm::vec2 scale) { _transform.set_scale(scale); recalculate_matrix(); }
}
