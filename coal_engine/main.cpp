#include "enpch.h"
#include "engine.h"

int main(int argc, char** argv) {
    engine::Logger::initialize_logger();

    engine::Engine* engine = engine::create_engine({ argc, argv });

    engine->run();

    delete engine;
}
