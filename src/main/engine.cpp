#include "engine.h"

#include <iostream>

Engine::Engine() {
}

int Engine::initialize() {
	if (glfwInit() == -1)
		return -1;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor(); // TODO: Handle no monitors error
	const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	_window = glfwCreateWindow(vidmode->width, vidmode->height, "Undertale", glfwGetPrimaryMonitor(), nullptr);
	if (!_window) {
		std::cout << "Failed to create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(_window);

	gladLoadGL();

	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);
	glViewport(0, 0, width, height);

	return 0;
}

void Engine::main_loop() {
	while (!should_close()) {
		update();
		draw();
		handle_input();
	}
}

void Engine::exit() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void Engine::handle_input() {
	glfwPollEvents();

	// process inputs
}

void Engine::update() {
	float time = (float)glfwGetTime();
	float delta = time - last_frame_time;
	last_frame_time = time;

	// process game with delta
}

void Engine::draw() {
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw objects

	glfwSwapBuffers(_window);
}

bool Engine::should_close() {
	return glfwWindowShouldClose(_window);
}