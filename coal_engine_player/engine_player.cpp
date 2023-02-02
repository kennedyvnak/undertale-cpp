#if ENGINE_PLAYER
// #define DISABLE_IMGUI
#include <coal_engine.h>
#include "player_layer.h"

namespace engine {
    namespace player {
        class EnginePlayer: public Engine {
        public:
            EnginePlayer(const EngineSpecification& specification)
                : Engine(specification) {
                push_layer(new PlayerLayer("player_layer"));
            }
        };
    }

    Engine* create_engine(EngineCommandLineArgs args) {
        EngineSpecification specification;
        specification.name = "Coal Engine Player";
        specification.command_line_args = args;
        return new player::EnginePlayer(specification);
    }
}
#endif // ENGINE_PLAYER
