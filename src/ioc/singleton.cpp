#include "pch.hpp"
#include "singleton.hpp"

namespace engine::ioc
{
    Singletons& Sing()
    {
        static Singletons s;
        return s;
    }
}
