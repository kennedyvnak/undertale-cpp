#pragma once 

namespace engine {
    using TimeValue = float;
    TimeValue operator "" _t(long double);

    class Time {
        friend class Engine;
    public:
        static TimeValue get_time_since_startup();
        static TimeValue get_time(); // TODO: Handle pause
        static TimeValue get_delta_time() { return _delta_time; }
    private:
        static TimeValue _delta_time;

        static void set_delta_time(TimeValue* _last_time_ptr);
    };
}
