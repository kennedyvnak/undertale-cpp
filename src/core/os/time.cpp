#include "time.h"
#include <GLFW/glfw3.h>

namespace engine {
    float Time::get_time_since_startup() {
        return float(get_time_since_startup_as_double());
    }
    double Time::get_time_since_startup_as_double() {
        return glfwGetTime();
    }
}