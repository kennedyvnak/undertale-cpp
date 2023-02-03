#pragma once

#include "event.h"
#include "core/input/mouse_codes.h"
#include "utility/string_utility.h"

namespace engine {
    class MouseMovedEvent: public Event {
    public:
        MouseMovedEvent(const float x, const float y)
            : _mouse_x(x), _mouse_y(y) { }

        float get_x() const { return _mouse_x; }
        float get_y() const { return _mouse_y; }

        std::string to_string()const override {
            return engine::format("MouseMovedEvent: ({}, {})", _mouse_x, _mouse_y);
        }

        ENGINE_EVENT_TYPE(Event_MouseMoved)
    private:
        float _mouse_x, _mouse_y;
    };

    class MouseScrolledEvent: public Event {
    public:
        MouseScrolledEvent(const float x_offset, const float y_offset)
            : _mouse_x_offset(x_offset), _mouse_y_offset(y_offset) { }

        float get_x_offset() const { return _mouse_x_offset; }
        float get_y_offset() const { return _mouse_y_offset; }

        std::string to_string()const override {
            return engine::format("MouseScrolledEvent: ({}, {})", _mouse_x_offset, _mouse_y_offset);
        }

        ENGINE_EVENT_TYPE(Event_MouseScrolled)
    private:
        float _mouse_x_offset, _mouse_y_offset;
    };

    class MouseButtonEvent: public Event {
    public:
        MouseCode get_mouse_button() const { return _button; }
    protected:
        MouseButtonEvent(const MouseCode button)
            : _button(button) {}

        MouseCode _button;
    };

    class MouseButtonPressedEvent: public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) { }

        std::string to_string() const override {
            return engine::format("MouseButtonPressedEvent: {}", _button);
        }

        ENGINE_EVENT_TYPE(Event_MouseButtonPressed)
    };

    class MouseButtonReleasedEvent: public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) { }

        std::string to_string() const override {
            return engine::format("MouseButtonReleasedEvent: {}", _button);
        }

        ENGINE_EVENT_TYPE(Event_MouseButtonReleased)
    };
}