#include "enpch.h"
#include "time.h"
#include <GLFW/glfw3.h>

namespace engine {
    TimeValue Time::_delta_time;

    TimeValue operator "" _t(long double value) {
        return TimeValue(value);
    }

    TimeValue Time::get_time_since_startup() {
        return static_cast<TimeValue>(glfwGetTime());
    }

    TimeValue Time::get_time() {
        return get_time_since_startup();
    }

    void Time::set_delta_time(TimeValue* _last_time_ptr) {
        TimeValue time = get_time();
        _delta_time = time - *_last_time_ptr;
        *_last_time_ptr = time;
    }
}
