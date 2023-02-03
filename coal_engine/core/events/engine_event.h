#pragma once

#include "event.h"

namespace engine {
    class EngineResizeViewportEvent: public Event {
    public:
        EngineResizeViewportEvent(unsigned int width, unsigned int height)
            : _width(width), _height(height) {}

        unsigned int get_width() const { return _width; }
        unsigned int get_height() const { return _height; }

        std::string to_string() const override {
            return engine::format("EngineResizeViewportEvent: {}x{}", _width, _height);
        }

        ENGINE_EVENT_TYPE(Event_EngineResizeViewport)
    private:
        unsigned int _width, _height;
    };
}