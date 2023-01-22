#include "enpch.h"
#include "engine.h"

using namespace engine;

int main(int argc, char** argv) {
    Logger::initialize_logger();

    Engine* engine = Engine::create_engine({ argc, argv });

    engine->run();

    delete engine;
}
