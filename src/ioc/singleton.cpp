#include "pch.hpp"
#include "ioc/singleton.hpp"

namespace engine::ioc
{
    Singletons& Sing()
    {
        static Singletons s;
        return s;
    }
}
