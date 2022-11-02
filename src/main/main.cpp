#include "engine.h"

int main() {
	Engine* engine = new Engine();

	int engine_initialize_r = engine->initialize();
	if (engine_initialize_r == -1)
		return -1;

	engine->main_loop();

	engine->exit();

	return 0;
}