#include "pch.hpp"
#include "ioc/container.hpp"

namespace engine::ioc
{
    Container& Get()
    {
        static Container c;
        return c;
    }
}
