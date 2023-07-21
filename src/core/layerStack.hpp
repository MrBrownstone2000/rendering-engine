#ifndef __LAYERSTACK_HPP__
#define __LAYERSTACK_HPP__

#include <vector>
#include "../util/types.hpp"

namespace engine
{
    class ILayer;

    class LayerStack
    {
        public:
            using LayerStackIterator = std::vector<ILayer*>::iterator;

            LayerStack() {};
            ~LayerStack();

            void pushLayer(ILayer* layer);
            void popLayer(ILayer* layer);

            void pushOverlay(ILayer* overlay);
            void popOverlay(ILayer* overlay);

            LayerStackIterator begin() { return m_layers.begin(); }
            LayerStackIterator end() { return m_layers.end(); }
        private:
            std::vector<ILayer*> m_layers;
            u32 m_layerInsertIndex = 0;
    };
}

#endif
