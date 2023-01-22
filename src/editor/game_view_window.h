#pragma once

#include <imgui.h>

namespace engine::editor {

    class GameViewWindow {
    public:
        GameViewWindow() = default;
        ~GameViewWindow() = default;

        void render();
    };
}