#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace engine {
	class Window {
	public:
		static const int min_width, min_height;

		Window(const std::string title);
		~Window();

		int init();

		void set_width(int width);
		void set_height(int height);
		void set_fullscreen(bool fullscreen);
		void set_vsync(bool enabled);

		inline const std::string& get_title() const& { return _title; }
		inline int get_width() const { return _width; }
		inline int get_height() const { return _height; }
		inline bool get_fullscreen() const { return _fullscreen; }
		inline bool get_vsync() const { return _vsync; }
		GLFWwindow* get_ptr() const { return _ptr; }

		void swap_buffers();
		void poll_events();
		bool should_close();

	private:
		std::string _title;
		int _width, _height;
		bool _fullscreen, _vsync;
		GLFWwindow* _ptr;

		void window_resized(GLFWwindow* window, int width, int height);
	};
}
