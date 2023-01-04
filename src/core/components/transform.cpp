#include "transform.h"

void Transform::recalculate_matrix() {
	_matrix = Matrix(1.0f);
	_matrix = glm::translate(_matrix, Vector3(_position, 0.0f));
	_matrix = glm::rotate(_matrix, glm::radians(_rotation), Vector3(0.0f, 0.0f, 1.0f));
	_matrix = glm::scale(_matrix, Vector3(_scale, 0.0f));
}

Transform::Transform() {
	Vector2 p = Vector2(0.0f);
	float r = 0.0f;
	Vector2 s = Vector2(1.0f);
	set_prs(p, r, s);
}

Transform::Transform(Vector2 position, float rotation, Vector2 scale) {
	set_prs(position, rotation, scale);
}

void Transform::set_prs(Vector2 position, float rotation, Vector2 scale) {
	_position = position;
	_rotation = rotation;
	_scale = scale;
	recalculate_matrix();
}
