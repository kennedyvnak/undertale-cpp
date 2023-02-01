#pragma once

#include "core/base.h"

namespace engine {
    enum class UniformType {
        None = -1, Float, Vec2, Vec3, Vec4, Mat4, Int
    };

    static unsigned int get_shader_uniform_type_size(UniformType type) {
        static const unsigned int FLOAT_SIZE = sizeof(float);
        static const unsigned int INT_SIZE = sizeof(int);

        switch (type) {
        case UniformType::Float: return FLOAT_SIZE;
        case UniformType::Vec2: return FLOAT_SIZE * 2;
        case UniformType::Vec3: return FLOAT_SIZE * 3;
        case UniformType::Vec4: return FLOAT_SIZE * 4;
        case UniformType::Mat4: return FLOAT_SIZE * FLOAT_SIZE * FLOAT_SIZE;
        case UniformType::Int: return INT_SIZE;
        }
        EN_ASSERT(false, "Unknow uniform type.");
        return 0;
    }

    struct BufferElement {
        std::string name;
        UniformType type;
        unsigned int size;
        unsigned long long offset;
        bool normalized;

        BufferElement() = default;
        BufferElement(UniformType type, const std::string& name, bool normalized = false)
            : name(name), type(type), size(get_shader_uniform_type_size(type)), offset(0), normalized(normalized) { }

        unsigned int get_component_count() const {
            switch (type) {
            case UniformType::Float: return 1;
            case UniformType::Vec2:  return 2;
            case UniformType::Vec3:  return 3;
            case UniformType::Vec4:  return 4;
            case UniformType::Mat4:  return 4; // 4 * Vec4
            case UniformType::Int:   return 1;
            }

            EN_ASSERT(false, "Unknow uniform type.");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() {}
        BufferLayout(std::initializer_list<BufferElement> elements)
            : _elements(elements) {
            calc_offset_and_stride();
        }

        unsigned int get_stride() const { return _stride; }
        const std::vector<BufferElement>& get_elements() const { return _elements; }

        std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
        std::vector<BufferElement>::iterator end() { return _elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
    private:
        std::vector<BufferElement> _elements;
        unsigned int _stride = 0;

        void calc_offset_and_stride() {
            size_t offset = 0;
            _stride = 0;
            for (auto& element : _elements) {
                element.offset = offset;
                offset += element.size;
                _stride += element.size;
            }
        }
    };

    class VertexBuffer {
    public:
        VertexBuffer(unsigned int size);
        VertexBuffer(unsigned int size, const void* vertices);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void set_data(unsigned int size, const void* data);

        const BufferLayout& get_layout() const { return _layout; }
        void set_layout(const BufferLayout& layout) { _layout = layout; }
    private:
        unsigned int _id;
        BufferLayout _layout;
    };

    class IndexBuffer {
    public:
        IndexBuffer(unsigned int* indices, unsigned int count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int get_count() const { return _count; }
    private:
        unsigned int _id;
        unsigned int _count;
    };
}