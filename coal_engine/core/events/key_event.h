#pragma once

#include "event.h"
#include "core/input/key_codes.h"
#include "utility/string_utility.h"

namespace engine {
    class KeyEvent: public Event {
    public:
        KeyCode get_code() const { return _keycode; }
    protected:
        KeyEvent(const KeyCode keycode)
            :_keycode(keycode) { }

        KeyCode _keycode;
    };

    class KeyPressedEvent: public KeyEvent {
    public:
        KeyPressedEvent(const KeyCode keycode, bool is_repeat = false)
            :KeyEvent(keycode), _is_repeat(is_repeat) { }

        bool is_repeat() const { return _is_repeat; }

        std::string to_string() const override {
            return engine::format("KeyPressedEvent: {} (repeat = {})", _keycode, _is_repeat);
        }

        ENGINE_EVENT_TYPE(Event_KeyPressed)
    private:
        bool _is_repeat;
    };

    class KeyReleasedEvent: public KeyEvent {
    public:
        KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string to_string() const override {
            return engine::format("KeyReleasedEvent: {}", _keycode);
        }

        ENGINE_EVENT_TYPE(Event_KeyReleased)
    };

    class KeyTypedEvent: public KeyEvent {
    public:
        KeyTypedEvent(const KeyCode keycode)
            :KeyEvent(keycode) {}

        std::string to_string() const override {
            return engine::format("KeyTypedEvent: {}", _keycode);
        }

        ENGINE_EVENT_TYPE(Event_KeyTyped)
    };
}