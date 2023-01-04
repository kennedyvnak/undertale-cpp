#pragma once

#include "engine.h"
#include <glm/gtc/matrix_transform.hpp>

class Transform {
private:
	Vector2 _position;
	float _rotation;
	Vector2 _scale;
	Matrix _matrix;

	void recalculate_matrix();

public:
	Transform();
	Transform(Vector2 position, float rotation, Vector2 scale);

	void set_prs(Vector2 position, float rotation, Vector2 scale);

	inline const Vector2 get_position() const& { return _position; }
	void set_position(Vector2 position) { _position = position; recalculate_matrix(); }

	inline const float get_rotation() const& { return _rotation; }
	void set_rotation(float rotation) { _rotation = rotation; recalculate_matrix(); }

	inline const Vector2 get_scale() const& { return _scale; }
	void set_scale(Vector2 scale) { _scale = scale; recalculate_matrix(); }

	inline const Matrix get_matrix() const& { return _matrix; }
};

