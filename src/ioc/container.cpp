#include "container.hpp"

namespace engine::ioc
{
    Container& Get()
    {
        static Container c;
        return c;
    }
}
