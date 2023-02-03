#pragma once 

#include "event.h"
#include "utility/string_utility.h"

namespace engine {
    class WindowResizeEvent: public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : _width(width), _height(height) {}

        unsigned int get_width() const { return _width; }
        unsigned int get_height() const { return _height; }

        std::string to_string() const override {
            return engine::format("WindowResizeEvent: {}x{}", _width, _height);
        }

        ENGINE_EVENT_TYPE(Event_WindowResize)
    private:
        unsigned int _width, _height;
    };

    class WindowCloseEvent: public Event {
    public:
        WindowCloseEvent() = default;

        ENGINE_EVENT_TYPE(Event_WindowClose)
    };
}