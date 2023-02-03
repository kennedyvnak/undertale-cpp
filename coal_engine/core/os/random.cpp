#include "random.h"
#include <ctime>
#include <cstdlib>

namespace engine {
    void Random::init() {
        srand(time(NULL));
    }

    int Random::randi() {
        return rand();
    }

    float Random::random_range(float min, float max) {
        return min + static_cast<float>(randi()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    float Random::randf() {
        return (float)randi() / RAND_MAX;
    }
}