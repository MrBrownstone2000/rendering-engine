#ifndef __LAYER_HPP__
#define __LAYER_HPP__

#include "../events/event.hpp"
#include <string>
namespace engine
{
    class ILayer
    {
        public:
            ILayer(const std::string& name = "Layer") : m_name(name) {}
            virtual ~ILayer() = 0;

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate() {}
            virtual void OnEvent(events::Event&) {}

            std::string GetName() const { return m_name; }

        protected:
            std::string m_name;
    };
    inline ILayer::~ILayer() = default;
}

#endif
