#include "pch.hpp"
#include "layerStack.hpp"
#include "layer.hpp"

namespace engine
{
    LayerStack::LayerStack()
    {
        m_layersInsert = m_layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (auto l : m_layers)
            delete l;
    }

    void LayerStack::PushLayer(ILayer* layer)
    {
        m_layersInsert = m_layers.emplace(m_layersInsert, layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(ILayer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            m_layersInsert--;
        }
        layer->OnDetach();
    }

    void LayerStack::PushOverlay(ILayer* overlay)
    {
        m_layers.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopOverlay(ILayer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
            m_layers.erase(it);
        overlay->OnDetach();
    }
}
