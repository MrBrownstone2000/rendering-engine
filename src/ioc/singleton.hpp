#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>

namespace engine::ioc
{
    class Singletons
    {
        public:
            template<class T>
            using Generator = std::function<std::shared_ptr<T>()>;

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
                        throw std::runtime_error( std::format("Could not resolve Singleton mapped type\nfrom: [{}]\nto: [{}]\n",
                                    entry.type().name(), typeid(Generator<T>).name()));
                    }
                }
                else
                    throw std::runtime_error{ std::format("Could not find generator for type [{}] in Singleton container",
                            typeid(T).name()) };
            }

        private:
            std::unordered_map<std::type_index, std::any> m_serviceMap;
    };

    Singletons& Sing();
}

#endif
