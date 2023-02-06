#include "enpch.h"
#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/math/math.h"

namespace engine {
	void Transform::recalculate_matrix() {
		_matrix = glm::mat4(1.0f);
		_matrix = glm::translate(_matrix, glm::vec3(_position, 0.0f));
		_matrix = glm::rotate(_matrix, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		_matrix = glm::scale(_matrix, glm::vec3(_scale, 0.0f));
	}

	Transform::Transform() {
		glm::vec2 p = glm::vec2(0.0f);
		float r = 0.0f;
		glm::vec2 s = glm::vec2(1.0f);
		set_prs(p, r, s);
	}

	Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale) {
		set_prs(position, rotation, scale);
	}

	void Transform::set_prs(glm::vec2 position, float rotation, glm::vec2 scale) {
		_position = position;
		_rotation = rotation;
		_scale = scale;
		recalculate_matrix();
	}

	void Transform::set_rotation(float rotation) {
		_rotation = Math::normalize(rotation, 0.0f, 360.0f);
		recalculate_matrix();
	}
}
