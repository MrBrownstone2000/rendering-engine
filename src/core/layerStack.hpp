#ifndef __LAYERSTACK_HPP__
#define __LAYERSTACK_HPP__

#include <vector>

namespace engine
{
    class ILayer;

    class LayerStack
    {
        public:
            using LayerStackIterator = std::vector<ILayer*>::iterator;

            LayerStack();
            ~LayerStack();

            void PushLayer(ILayer* layer);
            void PopLayer(ILayer* layer);

            void PushOverlay(ILayer* overlay);
            void PopOverlay(ILayer* overlay);

            LayerStackIterator begin() { return m_layers.begin(); }
            LayerStackIterator end() { return m_layers.end(); }
        private:
            std::vector<ILayer*> m_layers;
            LayerStackIterator m_layersInsert;
    };
}

#endif
