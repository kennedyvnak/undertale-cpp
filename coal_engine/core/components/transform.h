#pragma once

#include <glm/glm.hpp>

namespace engine {
	class Transform {
	private:
		glm::vec2 _position;
		float _rotation;
		glm::vec2 _scale;
		glm::mat4 _matrix;

		void recalculate_matrix();

	public:
		Transform();
		Transform(glm::vec2 position, float rotation, glm::vec2 scale);

		void set_prs(glm::vec2 position, float rotation, glm::vec2 scale);

		inline const glm::vec2 get_position() const& { return _position; }
		void set_position(glm::vec2 position) { _position = position; recalculate_matrix(); }

		inline const float get_rotation() const& { return _rotation; }
		void set_rotation(float rotation) { _rotation = rotation; recalculate_matrix(); }

		inline const glm::vec2 get_scale() const& { return _scale; }
		void set_scale(glm::vec2 scale) { _scale = scale; recalculate_matrix(); }

		inline const glm::mat4 get_matrix() const& { return _matrix; }
	};
}
