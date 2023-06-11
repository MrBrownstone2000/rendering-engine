#ifndef __LAYER_HPP__
#define __LAYER_HPP__

#include "events/event.hpp"
#include <string>
namespace engine
{
    class ILayer
    {
        public:
            ILayer(const std::string& name = "Layer") : m_name(name) {}
            virtual ~ILayer() = 0;

            void OnAttach() {}
            void OnDetach() {}
            void OnUpdate() {}
            void OnEvent(events::Event&) {}

            std::string GetName() const { return m_name; }

        protected:
            std::string m_name;
    };
    inline ILayer::~ILayer() = default;
}

#endif
