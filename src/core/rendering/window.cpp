#include "window.h"

namespace engine {
	Window::Window(const std::string title)
		: _title(title), _fullscreen(false), _width(0), _height(0), _ptr(nullptr), _vsync(false) { }

	Window::~Window() {
		glfwTerminate();
	}

	int Window::init() {
		if (glfwInit() == GLFW_FALSE)
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		if (_width == 0)
			_width = vidmode->width;
		if (_height == 0)
			_height = vidmode->height;

		_ptr = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

		if (_fullscreen)
			glfwSetWindowMonitor(_ptr, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);

		if (!_ptr) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(_ptr);

		glfwSwapInterval(_vsync);

		return 0;
	}

	void Window::set_width(int width) {
		_width = width;
		if (_ptr)
			glfwSetWindowSize(_ptr, _width, _height);
	}

	void Window::set_height(int height) {
		_height = height;
		if (_ptr)
			glfwSetWindowSize(_ptr, _width, _height);
	}

	void Window::set_fullscreen(bool fullscreen) {
		_fullscreen = fullscreen;

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(_ptr, _fullscreen ? monitor : NULL, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
	}

	void Window::set_vsync(bool enabled) {
		_vsync = enabled;
		if (_ptr)
			glfwSwapInterval(enabled);
	}

	void Window::swap_buffers() {
		glfwSwapBuffers(_ptr);
	}

	void Window::poll_events() {
		glfwPollEvents();
	}

	bool Window::should_close() {
		return glfwWindowShouldClose(_ptr);
	}
}