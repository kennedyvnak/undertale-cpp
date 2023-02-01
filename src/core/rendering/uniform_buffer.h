#pragma once 

#include "core/base.h"

namespace engine {
    class UniformBuffer {
    public:
        UniformBuffer(unsigned int size, unsigned int binding);
        ~UniformBuffer();
        void set_data(const void* data, unsigned int size, unsigned int offset = 0);

        inline unsigned int get_id() const { return _id; }
    private:
        unsigned int _id;
    };
}