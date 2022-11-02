#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Engine {
public:
	Engine();

	int initialize();
	void main_loop();
	void exit();

	void handle_input();
	void update();
	void draw();

	bool should_close();

	GLFWwindow* get_window() { return _window; }
	
private:
	float last_frame_time = 0;
	GLFWwindow* _window = nullptr;
};