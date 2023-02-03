#include "enpch.h"
#include "window.h"
#include "engine.h"
#include "core/events/window_event.h"

namespace engine {
	const int Window::min_width = 640;
	const int Window::min_height = 360;

	Window::Window(const std::string title) {
		_data.title = title;
	}

	Window::~Window() {
		glfwSetWindowSizeCallback(_ptr, nullptr);
		glfwDestroyWindow(_ptr);

		glfwTerminate();
	}

	void Window::init() {
		int sucess = glfwInit();
		EN_ASSERT(sucess, "Can't initialize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		if (_data.width <= 0)
			_data.width = vidmode->width;
		if (_data.height <= 0)
			_data.height = vidmode->height;

		_ptr = glfwCreateWindow(_data.width, _data.height, _data.title.c_str(), nullptr, nullptr);

		if (!_ptr) {
			glfwTerminate();
			EN_ASSERT(false, "Can't create GLFW window.");
		}

		glfwGetWindowPos(_ptr, nullptr, &start_y);

		if (_data.fullscreen)
			glfwSetWindowMonitor(_ptr, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);

		glfwSetWindowUserPointer(_ptr, &_data);
		glfwSetWindowSizeLimits(_ptr, Window::min_width, Window::min_height, GLFW_DONT_CARE, GLFW_DONT_CARE);

		glfwSetWindowSizeCallback(_ptr, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		data.minimized = width <= 0 && height <= 0;

		WindowResizeEvent event(width, height);
		data.event_callback(event);
			});

		glfwSetWindowCloseCallback(_ptr, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.event_callback(event);
			});

		glfwMakeContextCurrent(_ptr);

		glfwSwapInterval(_data.vsync);
	}

	void Window::set_width(int width) {
		_data.width = width;
		if (_ptr)
			glfwSetWindowSize(_ptr, width, _data.height);
	}

	void Window::set_height(int height) {
		_data.height = height;
		if (_ptr)
			glfwSetWindowSize(_ptr, _data.width, height);
	}

	void Window::set_fullscreen(bool fullscreen) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

		glfwSetWindowMonitor(_ptr, fullscreen ? monitor : NULL, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
		_data.fullscreen = fullscreen;

		glfwSetWindowPos(_ptr, 0, start_y);

		int posx, posy;
		glfwGetWindowPos(_ptr, &posx, &posy);
		EN_LOG_INFO("At ({}, {})", posx, posy);
	}

	void Window::set_vsync(bool enabled) {
		_data.vsync = enabled;
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
