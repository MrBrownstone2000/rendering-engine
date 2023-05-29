#ifndef __CONTAINER_HPP__
#define __CONTAINER_HPP__

#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <format>

#include "exception.hpp"
#include "../util/assert.hpp"

namespace engine::ioc
{
    template<class T>
    concept Parameterized = requires() {
        { typename T::IocParams{} };
    };

    template<class T>
    concept NotParameterized = !Parameterized<T>;

    class Container
    {
        public:
            template<class T>
            using Generator = std::function<std::shared_ptr<T>()>;
            template<class T>
            using ParameterizedGenerator = std::function<std::shared_ptr<T>(typename T::IocParams)>;

            template<NotParameterized T>
            void Register(Generator<T> gen)
            {
                m_serviceMap[typeid(T)] = std::move(gen);
            }

            template<Parameterized T>
            void Register(ParameterizedGenerator<T> gen)
            {
                m_serviceMap[typeid(T)] = std::move(gen);
            }

            template<NotParameterized T>
            std::shared_ptr<T> Resolve()
            {
                return Resolve_<T, Generator<T>>();
            }

            template<Parameterized T>
            std::shared_ptr<T> Resolve(typename T::IocParams&& params = {})
            {
                return Resolve_<T, ParameterizedGenerator<T>>(std::forward<typename T::IocParams>(params));
            }

        private:
            template<class T, class G, class...Ps>
            std::shared_ptr<T> Resolve_(Ps&& ...arg)
            {
                if (const auto i = m_serviceMap.find(typeid(T)); i != m_serviceMap.end())
                {
                    const std::any& entry = i->second;
                    try {
                        return std::any_cast<G>(entry)(std::forward<Ps>(arg)...);
                    } catch (const std::bad_cast&) {
                        Check(false).msg( std::format("Could not resolve IoC mapped type\nfrom: [{}]\nto: [{}]\n",
                                    entry.type().name(), typeid(Generator<T>).name())).ex();
                    }
                }
                else
                    throw ServiceNotFound{ std::format("Could not find generator for type [{}] in IoC container",
                            typeid(T).name()) };
            }

        private:
            std::unordered_map<std::type_index, std::any> m_serviceMap;
    };

    Container& Get();
}

#endif
