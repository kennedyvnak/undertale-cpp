#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(const std::string title);
	~Window();

	int init();

	void set_width(int width);
	void set_height(int height);
	void set_fullscreen(bool fullscreen);

	inline const std::string& get_title() const& { return _title; }
	inline int get_width() { return _width; }
	inline int get_height() { return _height; }
	inline bool get_fullscreen() { return _fullscreen; }
	GLFWwindow* get_ptr() { return _ptr; }

	void swap_buffers();
	bool should_close();

private:
	std::string _title;
	int _width, _height;
	bool _fullscreen;
	GLFWwindow* _ptr;
};