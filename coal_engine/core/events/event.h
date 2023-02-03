#pragma once 

#include "core/base.h"

#include <string>
#include <functional>

namespace engine {
    enum EventType {
        None = 0,
        Event_WindowClose, Event_WindowResize, Event_WindowFocus,
        Event_EngineTick, Event_EngineUpdate, Event_EngineRender, Event_EngineResizeViewport,
        Event_KeyPressed, Event_KeyReleased, Event_KeyTyped,
        Event_MouseButtonPressed, Event_MouseButtonReleased, Event_MouseMoved, Event_MouseScrolled
    };

#define ENGINE_EVENT_TYPE(type) static EventType get_static_type() { return EventType::type; }\
                                virtual EventType get_type() const override { return get_static_type(); }\
                                virtual const char* get_name() const override { return #type; }

    class Event {
    public:
        virtual ~Event() = default;
        bool handled = false;

        virtual EventType get_type() const = 0;
        virtual const char* get_name() const = 0;
        virtual std::string to_string() const { return get_name(); }
    };

    class EventDispatcher {
    public:
        EventDispatcher(Event& event)
            : _event(event) {}

        template<typename T, typename Func>
        bool dispatch(const Func& func) {
            if (_event.get_type() == T::get_static_type()) {
                _event.handled |= func(static_cast<T&>(_event));
                return true;
            }
            return false;
        }
    private:
        Event& _event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.to_string();
    }
}