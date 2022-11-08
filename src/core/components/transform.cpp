#include "transform.h"

void Transform::recalculate_matrix() {
	_matrix = mat4(1.0f);
	_matrix = translate(_matrix, vec3(_position, 0.0f));
	_matrix = rotate(_matrix, radians(_rotation), vec3(0.0f, 0.0f, 1.0f));
	_matrix = scale(_matrix, vec3(_scale, 0.0f));
}

Transform::Transform() {
	vec2 p = vec2(0.0f);
	float r = 0.0f;
	vec2 s = vec2(1.0f);
	set_prs(p, r, s);
}

Transform::Transform(vec2 position, float rotation, vec2 scale) {
	set_prs(position, rotation, scale);
}

void Transform::set_prs(vec2 position, float rotation, vec2 scale) {
	_position = position;
	_rotation = rotation;
	_scale = scale;
	recalculate_matrix();
}
