#pragma once 

namespace engine {
    class Time {
    public:
        static float get_time_since_startup();
        static double get_time_since_startup_as_double();
    };
}
