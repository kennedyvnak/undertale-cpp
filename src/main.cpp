#include "enpch.h"
#include "engine.h"

using namespace engine;

int main(int argc, char** argv) {
    Logger::initialize_logger();

    EN_LOG_TRACE("Trace");
    EN_LOG_INFO("Info");
    EN_LOG_WARNING("Warning");
    EN_LOG_ERROR("Error");
    EN_LOG_CRITICAL("Critical");

    Engine* engine = Engine::create_engine({ argc, argv });

    engine->run();

    delete engine;
}
