#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/components/transform.h"

class Camera {
private:
	Transform _transform;
	glm::mat4 _projection, _view_projection;
	void recalculate_matrix();

public:
	Camera();
	Camera(float left, float right, float top, float bottom, float near, float far);

	void set_bounds(float left, float right, float top, float bottom, float near, float far);

	inline const glm::mat4 get_projection() const& { return _projection; }
	void set_projection(glm::mat4 value) { _projection = value; recalculate_matrix(); }

	inline const glm::mat4 get_view_projection() const& { return _view_projection; }

	inline Transform& get_transform() { return _transform; }
	void set_position(glm::vec2 position) { _transform.set_position(position); recalculate_matrix(); }
	void set_rotation(float rotation) { _transform.set_rotation(rotation); recalculate_matrix(); }
	void set_scale(glm::vec2 scale) { _transform.set_scale(scale); recalculate_matrix(); }
};

