#pragma once

namespace engine {
    struct Math {
        template<typename T>
        static T normalize(const T value, const T start, const T end) {
            if constexpr (std::is_floating_point<T>()) {
                const float width = end - start;
                const float offset_value = value - start;

                return (offset_value - (floor(offset_value / width) * width)) + start;
            } else {
                const T width = end - start;
                const T offset_value = value - start;

                return (offset_value - ((offset_value / width) * width)) + start;
            }
        }
    };
}