#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__


#include "container.hpp"
#include "../util/debug.hpp"

namespace engine::ioc
{
    class Singletons
    {
        public:
            template<class T>
            using Generator = std::function<std::shared_ptr<T>()>;

            template<class T>
            void RegisterPassThru()
            {
                Register<T>([] { return ioc::Get().Resolve<T>(); });
            }

            template<class T>
            void Register(Generator<T> gen)
            {
                m_serviceMap[typeid(T)] = std::move(gen);
            }

            template<class T>
            std::shared_ptr<T> Resolve()
            {
                if (const auto i = m_serviceMap.find(typeid(T)); i != m_serviceMap.end())
                {
                    std::any& entry = i->second;
                    try {
                        // Check if instance already exists
                        if (auto ppInstance = std::any_cast<std::shared_ptr<T>>(&entry))
                            return *ppInstance;

                        auto pInstance = std::any_cast<Generator<T>>(entry)();
                        entry = pInstance;
                        return pInstance;
                    } catch (const std::bad_cast&) {
                        Check(false).msg(
                            std::format("Could not resolve Singleton mapped type\nfrom: [{}]\nto: [{}]\n",
                                Demangle(entry.type().name()),
                                Demangle(typeid(Generator<T>).name())
                        )).ex();
                    }
                }
                else
                    throw ServiceNotFound{ std::format("Could not find generator for type [{}] in Singleton container",
                            Demangle(typeid(T).name())) };
            }

        private:
            std::unordered_map<std::type_index, std::any> m_serviceMap;
    };

    Singletons& Sing();
}

#endif
