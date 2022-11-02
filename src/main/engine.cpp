#include "engine.h"

#include <iostream>

Engine::Engine() {
}

int Engine::initialize() {
	if (glfwInit() == -1)
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
	_window = glfwCreateWindow(window_width, window_height, "Undertale", nullptr, nullptr);
	if (!_window) {
		std::cout << "Failed to create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_window);

	gladLoadGL();

	glViewport(0, 0, window_width, window_height);

	return 0;
}

void Engine::main_loop() {
	while (!should_close()) {
		handle_input();
		update();
		draw();
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
