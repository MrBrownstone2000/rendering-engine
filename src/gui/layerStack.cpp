#include "pch.hpp"
#include "gui/layerStack.hpp"
#include "gui/layer.hpp"

namespace engine
{
    LayerStack::~LayerStack()
    {
        for (auto l : m_layers)
            delete l;
    }

    void LayerStack::pushLayer(ILayer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
        m_layerInsertIndex++;
    }

    void LayerStack::popLayer(ILayer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            m_layerInsertIndex--;
        }
    }

    void LayerStack::pushOverlay(ILayer* overlay)
    {
        m_layers.emplace_back(overlay);
    }

    void LayerStack::popOverlay(ILayer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
            m_layers.erase(it);
    }
}
