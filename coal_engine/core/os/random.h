#pragma once 

namespace engine {
    class Random {
    public:
        static void init();
        /// @brief Generate a random integer
        /// @return A integer between 0 and RAND_MAX (currently 0x7fff)
        static int randi();
        /// @brief Generate a random float
        /// @return A float between 0.0 and 1.0
        static float randf();
        static float random_range(float min, float max);
    };
}