#pragma once 

#include "layer.h"

namespace engine {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void push_layer(Layer* layer);
        void push_overlay(Layer* overlay);
        void pop_layer(Layer* layer);
        void pop_overlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return _layers.begin(); }
        std::vector<Layer*>::iterator end() { return _layers.end(); }
    private:
        std::vector<Layer*> _layers;
        unsigned int _layer_insert_index = 0;
    };
}